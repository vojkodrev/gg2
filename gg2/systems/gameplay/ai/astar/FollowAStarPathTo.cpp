#include "FollowAStarPathTo.h"
#include <atomic>
#include "HasReachedRect.h"
#include "MoveColCenterToward.h"
#include "../../../../structs/core/constants/ConcussiveShotConstants.h"
#include "NpcMonsterConstants.h"
#include "RequestAStarPath.h"
#include "../../../../utils/timers/RandomTimer.h"

void followAStarPathTo(uint32_t n, Context &ctx, SDL_FRect targetCol)
{
    auto &ai = ctx.data.npc.ai;
    float dt = ctx.frame.dt;

    // acquire: pairs with release store in RequestAStarPath, ensures path data is visible
    auto pathStatus = ai.path.status[n].load(std::memory_order_acquire);

    if (pathStatus == NPCPathStatus::IDLE ||
        pathStatus == NPCPathStatus::CALCULATION_FAILED)
    {
        ai.repathTimer[n] = randomTimer(NPC_REPATH_TIME_MIN, NPC_REPATH_TIME_MAX);
        requestAStarPath(ctx, n, targetCol);
    }
    else if (pathStatus == NPCPathStatus::CALCULATION_FINISHED)
    {
        ai.repathTimer[n] -= dt;
        if (ai.repathTimer[n] <= 0.0f)
        {
            ai.path.status[n].store(NPCPathStatus::IDLE, std::memory_order_relaxed);
            return;
        }

        uint32_t len = ai.path.length[n];
        uint32_t prevIndex = ai.path.index[n];
        uint32_t i = prevIndex;

        while (i + 1 < len && hasReachedRect(ctx, n, { (float)ai.path.point.x[n][i], (float)ai.path.point.y[n][i], 1, 1 }))
            i++;
        ai.path.index[n] = i;
        if (i != prevIndex)
            ai.repathTimer[n] = randomTimer(NPC_REPATH_TIME_MIN, NPC_REPATH_TIME_MAX);

        SDL_FPoint target = { (float)ai.path.point.x[n][i], (float)ai.path.point.y[n][i] };
        const bool isConcussed = ctx.data.npc.concussiveShotDebuffTimer[n] > 0.0f;
        const float moveSpeed = isConcussed ?
            NPC_MONSTER_SPEED * CONCUSSIVE_SHOT_SPEED_MULTIPLIER :
            NPC_MONSTER_SPEED;
        moveNpcColCenterToward(ctx, n, target, moveSpeed);

        if (i + 1 >= len && hasReachedRect(ctx, n, { target.x, target.y, 1, 1 }))
            ai.path.status[n].store(NPCPathStatus::IDLE, std::memory_order_relaxed);
    }
}
