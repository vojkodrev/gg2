#include "IsBlocked.h"
#include "EntityColAABBObject.h"
#include "EntityColAABBNPC.h"
#include "ColId.h"
#include "Constants.h"
#include <SDL3/SDL.h>
#include "spatialhash/SpatialHashQuery.h"
#include "../../../../../utils/collision/CenteredRect.h"

bool isBlocked(const AStarContext& astar, const Context& ctx, SDL_Point node, int npcIndex)
{
    SDL_FRect npcCol = entityColAABB(ctx.data.npc, npcIndex);
    SDL_FRect moverBox = centeredRect({(float)node.x, (float)node.y}, npcCol.w, npcCol.h, NPC_MONSTER_PATH_STEP);

    uint16_t candidates[SpatialHash::MAX_PER_BUCKET * 4];
    int n = spatialHashQuery(astar.colHashSnapshot, moverBox, candidates, SpatialHash::MAX_PER_BUCKET * 4);

    for (int i = 0; i < n; i++)
    {
        uint16_t id = candidates[i];
        SDL_FRect box;
        if (colIdIsObject(id))
            box = entityColAABB(ctx.data.object, colIdObjectIndex(id));
        else if (colIdIsNpc(id) && (int)colIdNpcIndex(id) != npcIndex)
            box = entityColAABB(ctx.data.npc, colIdNpcIndex(id));
        else
            continue;

        if (SDL_HasRectIntersectionFloat(&moverBox, &box))
            return true;
    }
    return false;
}
