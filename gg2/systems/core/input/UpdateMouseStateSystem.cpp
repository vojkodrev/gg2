#include "UpdateMouseStateSystem.h"
#include <SDL3/SDL.h>

void updateMouseStateSystem(Context &ctx)
{
    SDL_GetMouseState(&ctx.mouse.x, &ctx.mouse.y);
}
