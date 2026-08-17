#include "HasReachedRect.h"
#include "MainEntityColAABB.h"
#include <SDL3/SDL.h>

bool hasReachedRect(Context &ctx, uint32_t n, SDL_FRect target)
{
    SDL_FRect col = mainEntityColAABB(ctx.data.npc.base, n);
    return SDL_HasRectIntersectionFloat(&col, &target);
}
