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
    const bool showCollision = ctx.data.debug.showCollision;
    const bool showNavigation = ctx.data.debug.showNavigation;

    if (showCollision)
    {
        debugRenderPlayer(ctx, off, screen);
        debugRenderObjects(ctx, off, screen);
    }

    if (showCollision || showNavigation)
        debugRenderNpc(ctx, off, screen);

    if (showNavigation)
        debugRenderAstar(ctx, off, screen);
}
