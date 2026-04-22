#include "UpdateFrameStateSystem.h"
#include <SDL3/SDL.h>

void updateFrameStateSystem(Context &ctx)
{
    ctx.frame.now = SDL_GetTicks();
    ctx.frame.dt = (ctx.frame.now - ctx.frame.lastTicks) / 1000.0f;
    ctx.frame.lastTicks = ctx.frame.now;
}
