#include "IsBlocked.h"
#include "EntityAABB.h"
#include "ColId.h"
#include "Constants.h"
#include <SDL3/SDL.h>

bool isBlocked(const AStarContext& astar, const Context& ctx, int wx, int wy, SDL_FRect startCol)
{
    SDL_FRect moverBox = { (float)wx - startCol.w * 0.5f - NPC_MONSTER_PATH_STEP,
                           (float)wy - startCol.h * 0.5f - NPC_MONSTER_PATH_STEP,
                           startCol.w + NPC_MONSTER_PATH_STEP * 2,
                           startCol.h + NPC_MONSTER_PATH_STEP * 2 };

    uint16_t candidates[SpatialHash::MAX_PER_BUCKET * 4];
    int n = astar.colHashSnapshot.query(moverBox.x, moverBox.y, moverBox.w, moverBox.h,
                                        candidates, SpatialHash::MAX_PER_BUCKET * 4);

    for (int i = 0; i < n; i++)
    {
        uint16_t id = candidates[i];
        if (!colIdIsObject(id))
            continue;

        SDL_FRect box = entityColAABB(ctx.data.object, colIdObjectIndex(id));

        if (SDL_HasRectIntersectionFloat(&moverBox, &box))
            return true;
    }
    return false;
}
