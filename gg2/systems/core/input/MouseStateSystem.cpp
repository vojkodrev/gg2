#include "MouseStateSystem.h"
#include <SDL3/SDL.h>

void mouseStateSystem(Context &ctx)
{
    SDL_GetMouseState(&ctx.mouse.x, &ctx.mouse.y);
}
