#include "DebugRenderSystem.h"
#include "DebugRenderPlayer.h"
#include "DebugRenderNpc.h"
#include "DebugRenderObjects.h"
#include "DebugRenderAstar.h"

void debugRenderSystem(const Context &ctx)
{
    const SDL_FPoint off = ctx.data.camera.offset;
    const SDL_FRect screen = ctx.data.camera.screen;

    debugRenderPlayer(ctx, off, screen);
    debugRenderObjects(ctx, off, screen);
    debugRenderNpc(ctx, off, screen);
    debugRenderAstar(ctx, off, screen);
}
