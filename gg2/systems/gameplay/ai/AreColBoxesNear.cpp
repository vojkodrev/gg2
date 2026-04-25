#include "AreColBoxesNear.h"
#include "EntityAABB.h"
#include <SDL3/SDL.h>

bool areColBoxesNear(Context &ctx, uint32_t n, const SDL_FRect &targetCol, float buffer)
{
    SDL_FRect expanded = {targetCol.x - buffer, targetCol.y - buffer,
                          targetCol.w + buffer * 2, targetCol.h + buffer * 2};
    SDL_FRect npcCol = entityColAABB(ctx.data.npc, n);
    return SDL_HasRectIntersectionFloat(&npcCol, &expanded);
}
