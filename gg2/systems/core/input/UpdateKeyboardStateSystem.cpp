#include "UpdateKeyboardStateSystem.h"
#include <SDL3/SDL.h>

void updateKeyboardStateSystem(Context &ctx)
{
    const bool *keys = SDL_GetKeyboardState(nullptr);
    ctx.keyboard.w = keys[SDL_SCANCODE_W];
    ctx.keyboard.a = keys[SDL_SCANCODE_A];
    ctx.keyboard.s = keys[SDL_SCANCODE_S];
    ctx.keyboard.d = keys[SDL_SCANCODE_D];
    ctx.keyboard.ctrl = keys[SDL_SCANCODE_LCTRL] || keys[SDL_SCANCODE_RCTRL];
    ctx.keyboard.shift = keys[SDL_SCANCODE_LSHIFT] || keys[SDL_SCANCODE_RSHIFT];
    ctx.keyboard.alt = keys[SDL_SCANCODE_LALT] || keys[SDL_SCANCODE_RALT];
    ctx.keyboard.digit0 = keys[SDL_SCANCODE_0];
    ctx.keyboard.digit1 = keys[SDL_SCANCODE_1];
    ctx.keyboard.digit2 = keys[SDL_SCANCODE_2];
    ctx.keyboard.digit3 = keys[SDL_SCANCODE_3];
    ctx.keyboard.digit4 = keys[SDL_SCANCODE_4];
    ctx.keyboard.digit5 = keys[SDL_SCANCODE_5];
    ctx.keyboard.digit6 = keys[SDL_SCANCODE_6];
    ctx.keyboard.digit7 = keys[SDL_SCANCODE_7];
    ctx.keyboard.digit8 = keys[SDL_SCANCODE_8];
    ctx.keyboard.digit9 = keys[SDL_SCANCODE_9];
}
