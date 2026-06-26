#include "MouseStateSystem.h"
#include <SDL3/SDL.h>

void mouseStateSystem(Context &ctx)
{
    SDL_MouseButtonFlags buttons = SDL_GetMouseState(&ctx.mouse.x, &ctx.mouse.y);
    ctx.mouse.leftClicked = (buttons & SDL_BUTTON_LMASK) != 0;
}
