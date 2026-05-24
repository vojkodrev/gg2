#include "DebugRenderSystem.h"
#include "DebugRenderPlayer.h"
#include "DebugRenderNpc.h"
#include "DebugRenderObjects.h"
#include "DebugRenderAstar.h"

void debugRenderSystem(const Context &ctx)
{
    const SDL_FPoint off = ctx.data.camera.offset;
    const SDL_FRect screen = ctx.data.camera.screen;
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
