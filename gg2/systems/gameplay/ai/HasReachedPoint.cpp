#include "HasReachedPoint.h"
#include "EntityAABB.h"
#include <SDL3/SDL.h>

bool hasReachedPoint(Context &ctx, uint32_t n, SDL_FPoint target)
{
    SDL_FRect col = entityColAABB(ctx.data.npc, n);
    return SDL_PointInRectFloat(&target, &col);
}
