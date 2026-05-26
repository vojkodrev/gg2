#include "AreColBoxesNear.h"
#include "EntityBaseColAABB.h"
#include <SDL3/SDL.h>

bool areColBoxesNear(Context &ctx, uint32_t n, const SDL_FRect &targetCol, float buffer)
{
    SDL_FRect npcCol = entityBaseColAABB(ctx.data.npc.base, n, buffer);
    return SDL_HasRectIntersectionFloat(&npcCol, &targetCol);
}
