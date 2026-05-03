#include "UpdateAStarPath.h"
#include <atomic>
#include "HasReachedRect.h"
#include "MoveColCenterToward.h"
#include "Constants.h"
#include "RequestAStarPath.h"

void updateAStarPath(uint32_t n, Context &ctx, SDL_FRect targetCol)
{
    auto &ai = ctx.data.npc.ai;

    // acquire: pairs with release store in RequestAStarPath, ensures path data is visible
    auto pathStatus = ai.path.status[n].load(std::memory_order_acquire);

    if (pathStatus == NPCPathStatus::IDLE ||
        pathStatus == NPCPathStatus::CALCULATION_FAILED)
    {
        requestAStarPath(ctx, n, targetCol);
    }
    else if (pathStatus == NPCPathStatus::CALCULATION_FINISHED)
    {
        uint32_t len = ai.path.length[n];
        uint32_t i = ai.path.index[n];

        while (i + 1 < len && hasReachedRect(ctx, n, { (float)ai.path.point.x[n][i], (float)ai.path.point.y[n][i], 1, 1 }))
            i++;
        ai.path.index[n] = i;

        SDL_FPoint target = { (float)ai.path.point.x[n][i], (float)ai.path.point.y[n][i] };
        moveColCenterToward(ctx, n, target, NPC_MONSTER_SPEED);

        if (i + 1 >= len && hasReachedRect(ctx, n, { target.x, target.y, 1, 1 }))
            ai.path.status[n].store(NPCPathStatus::IDLE, std::memory_order_relaxed);
    }
}
