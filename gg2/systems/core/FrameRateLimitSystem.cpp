#include "FrameRateLimitSystem.h"
#include <SDL3/SDL.h>

void FrameRateLimitSystem(Context &ctx)
{
    ctx.frame.frameTime = SDL_GetTicks() - ctx.frame.now;
    ctx.frame.targetTime = 1000 / ctx.frame.maxFps;
    if (ctx.frame.frameTime < ctx.frame.targetTime)
        SDL_Delay(ctx.frame.targetTime - ctx.frame.frameTime);

    if (++ctx.frame.frameCount % 60 == 0)
        SDL_Log("frame: %llu ms", ctx.frame.frameTime);
}
