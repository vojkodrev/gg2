#include "DebugRenderSystem.h"
#include "DebugRenderPlayer.h"
#include "DebugRenderNpc.h"
#include "DebugRenderObjects.h"
#include "DebugRenderAstar.h"
#include "../../gameplay/camera/GetCameraOffset.h"

void debugRenderSystem(const Context &ctx)
{
    SDL_FPoint off = getCameraOffset(ctx);
    SDL_FRect screen = {0, 0, ctx.data.camera.position.w[0], ctx.data.camera.position.h[0]};

    debugRenderPlayer(ctx.renderer, ctx, off, screen);
    debugRenderNpc(ctx.renderer, ctx, off, screen);
    debugRenderObjects(ctx.renderer, ctx, off, screen);
    debugRenderAstar(ctx.renderer, ctx, off, screen);
}
