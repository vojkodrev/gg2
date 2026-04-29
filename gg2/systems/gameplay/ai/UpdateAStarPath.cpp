#include "UpdateAStarPath.h"
#include <atomic>
#include "HasReachedPoint.h"
#include "MoveColCenterToward.h"
#include "Constants.h"
#include "astar/RequestAStarPath.h"

void updateAStarPath(uint32_t n, Context &ctx, SDL_FRect targetCol)
{
    auto &ai = ctx.data.npc.ai;

    // acquire: pairs with release store in RequestAStarPath, ensures path data is visible
    auto pathStatus = ai.pathStatus[n].load(std::memory_order_acquire);

    if (pathStatus == NPCPathStatus::IDLE ||
        pathStatus == NPCPathStatus::CALCULATION_FAILED)
    {
        requestAStarPath(ctx, n, targetCol);
    }
    else if (pathStatus == NPCPathStatus::CALCULATION_FINISHED)
    {
        uint32_t len = ai.pathLength[n];
        uint32_t i = ai.pathIndex[n];

        while (i + 1 < len && hasReachedPoint(ctx, n, { (float)ai.path.x[n][i], (float)ai.path.y[n][i] }))
            i++;
        ai.pathIndex[n] = i;

        SDL_FPoint target = { (float)ai.path.x[n][i], (float)ai.path.y[n][i] };
        moveColCenterToward(ctx, n, target, NPC_MONSTER_SPEED);

        if (i + 1 >= len && hasReachedPoint(ctx, n, target))
            ai.pathStatus[n].store(NPCPathStatus::IDLE, std::memory_order_relaxed);
    }
}
