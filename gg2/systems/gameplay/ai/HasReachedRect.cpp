#include "HasReachedRect.h"
#include "EntityColAABB.h"
#include <SDL3/SDL.h>

bool hasReachedRect(Context &ctx, uint32_t n, SDL_FRect target)
{
    SDL_FRect col = entityColAABB(ctx.data.npc.base, n);
    return SDL_HasRectIntersectionFloat(&col, &target);
}
