#include "HasReachedPoint.h"
#include "EntityAABB.h"
#include <SDL3/SDL.h>

bool hasReachedPoint(Context &ctx, uint32_t n, float tx, float ty)
{
    SDL_FRect col = entityColAABB(ctx.data.npc, n);
    SDL_FPoint point = {tx, ty};
    return SDL_PointInRectFloat(&point, &col);
}
