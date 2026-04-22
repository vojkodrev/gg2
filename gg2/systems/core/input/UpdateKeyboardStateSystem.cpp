#include "UpdateKeyboardStateSystem.h"
#include <SDL3/SDL.h>

void updateKeyboardStateSystem(Context &ctx)
{
    const bool *keys = SDL_GetKeyboardState(nullptr);
    ctx.keyboard.w = keys[SDL_SCANCODE_W];
    ctx.keyboard.a = keys[SDL_SCANCODE_A];
    ctx.keyboard.s = keys[SDL_SCANCODE_S];
    ctx.keyboard.d = keys[SDL_SCANCODE_D];
}
