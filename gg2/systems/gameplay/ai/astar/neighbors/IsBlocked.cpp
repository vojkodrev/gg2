#include "IsBlocked.h"
#include "EntityColAABB.h"
#include "ColIdIndex.h"
#include "ColIdType.h"
#include <SDL3/SDL.h>
#include "spatialhash/SpatialHashQuery.h"
#include "spatialhash/SpatialHashConstants.h"
#include "../../../../../utils/rect/CenteredRect.h"

template<uint32_t N>
bool isBlocked(const AStarContext<N>& astar, uint32_t astarIndex, const Context& ctx, SDL_Point node, int npcIndex)
{
    SDL_FRect npcCol = entityColAABB(ctx.data.npc.base, npcIndex);
    SDL_FRect moverBox = centeredRect({(float)node.x, (float)node.y}, npcCol.w, npcCol.h);

    uint32_t candidates[SPATIAL_HASH_MAX_PER_BUCKET * 4];
    int n = spatialHashQuery(astar.colHashSnapshot, astarIndex, moverBox, candidates, SPATIAL_HASH_MAX_PER_BUCKET * 4);

    for (int i = 0; i < n; i++)
    {
        uint32_t id = candidates[i];
        ColType type = colIdType(id);
        SDL_FRect box;
        if (type == ColType::Object)
            box = entityColAABB(ctx.data.object.base, colIdIndex(id));
        else if (type == ColType::NPC && (int)colIdIndex(id) != npcIndex)
            box = entityColAABB(ctx.data.npc.base, colIdIndex(id));
        else
            continue;

        if (SDL_HasRectIntersectionFloat(&moverBox, &box))
            return true;
    }
    return false;
}
