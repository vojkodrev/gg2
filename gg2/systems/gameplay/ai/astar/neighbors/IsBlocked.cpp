#include "IsBlocked.h"
#include "EntityColAABBObject.h"
#include "ColId.h"
#include "Constants.h"
#include <SDL3/SDL.h>
#include "spatialhash/SpatialHashQuery.h"

bool isBlocked(const AStarContext& astar, const Context& ctx, SDL_Point node, SDL_FRect startCol)
{
    SDL_FRect moverBox = { (float)node.x - startCol.w * 0.5f - NPC_MONSTER_PATH_STEP,
                           (float)node.y - startCol.h * 0.5f - NPC_MONSTER_PATH_STEP,
                           startCol.w + NPC_MONSTER_PATH_STEP * 2,
                           startCol.h + NPC_MONSTER_PATH_STEP * 2 };

    uint16_t candidates[SpatialHash::MAX_PER_BUCKET * 4];
    int n = spatialHashQuery(astar.colHashSnapshot, moverBox, candidates, SpatialHash::MAX_PER_BUCKET * 4);

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
