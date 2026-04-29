#include "AreColBoxesNear.h"
#include "EntityColAABBNPC.h"
#include <SDL3/SDL.h>

bool areColBoxesNear(Context &ctx, uint32_t n, const SDL_FRect &targetCol, float buffer)
{
    SDL_FRect npcCol = entityColAABB(ctx.data.npc, n, buffer);
    return SDL_HasRectIntersectionFloat(&npcCol, &targetCol);
}
