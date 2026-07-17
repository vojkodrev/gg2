#include "FollowAStarPathTo.h"
#include <atomic>
#include "HasReachedRect.h"
#include "MoveColCenterToward.h"
#include "../../../../structs/core/constants/ConcussiveShotConstants.h"
#include "../../../../utils/collision/EntityColCenter.h"
#include "../../../../utils/math/Dist.h"
#include "NpcMonsterConstants.h"
#include "RequestAStarPath.h"

void followAStarPathTo(
    uint32_t n, 
    Context &ctx, 
    SDL_FRect targetCol, 
    int targetNpcIndex)
{
    auto &ai = ctx.data.npc.ai;

    // acquire: pairs with release store in RequestAStarPath, ensures path data is visible
    auto pathStatus = ai.path.status[n].load(std::memory_order_acquire);

    if (pathStatus == NPCPathStatus::IDLE ||
        pathStatus == NPCPathStatus::CALCULATION_FAILED)
    {
        ai.repathTimer[n] = NPC_REPATH_TIME;
        ai.pathTargetCheckTimer[n] = NPC_PATH_TARGET_CHECK_TIME;
        requestAStarPath(ctx, n, targetCol, targetNpcIndex);
    }
    else if (pathStatus == NPCPathStatus::CALCULATION_FINISHED)
    {
        const uint32_t len = ai.path.length[n];
        if (ai.pathTargetCheckTimer[n] <= 0.0f)
        {
            ai.pathTargetCheckTimer[n] = NPC_PATH_TARGET_CHECK_TIME;
            const SDL_FPoint targetCenter = entityColCenter(targetCol);
            const uint32_t lastPathIndex = len - 1;
            if (dist(
                    (float)ai.path.point.x[n][lastPathIndex],
                    (float)ai.path.point.y[n][lastPathIndex],
                    targetCenter.x,
                    targetCenter.y) >=
                NPC_PATH_TARGET_MOVE_THRESHOLD)
            {
                ai.path.status[n].store(NPCPathStatus::IDLE, std::memory_order_relaxed);
                return;
            }
        }

        if (ai.repathTimer[n] <= 0.0f)
        {
            ai.path.status[n].store(NPCPathStatus::IDLE, std::memory_order_relaxed);
            return;
        }

        uint32_t prevIndex = ai.path.index[n];
        uint32_t i = prevIndex;

        while (i + 1 < len && hasReachedRect(ctx, n, { (float)ai.path.point.x[n][i], (float)ai.path.point.y[n][i], 1, 1 }))
            i++;
        ai.path.index[n] = i;
        if (i != prevIndex)
            ai.repathTimer[n] = NPC_REPATH_TIME;

        SDL_FPoint target = { (float)ai.path.point.x[n][i], (float)ai.path.point.y[n][i] };
        const auto &debuff = ctx.data.npc.concussiveShotDebuff;
        bool isConcussed = false;
        for (uint32_t j = 0; j < MAX_DEBUFF_SLOTS; j++)
            isConcussed = isConcussed || debuff.pool.active[n][j];
        const float moveSpeed = isConcussed ?
            NPC_MONSTER_SPEED * CONCUSSIVE_SHOT_SPEED_MULTIPLIER :
            NPC_MONSTER_SPEED;
        moveNpcColCenterToward(ctx, n, target, moveSpeed);

        if (i + 1 >= len && hasReachedRect(ctx, n, { target.x, target.y, 1, 1 }))
            ai.path.status[n].store(NPCPathStatus::IDLE, std::memory_order_relaxed);
    }
}
