#include "DebugRenderSystem.h"
#include "DebugRenderPlayer.h"
#include "DebugRenderNpc.h"
#include "DebugRenderObjects.h"
#include "DebugRenderEffect.h"
#include "DebugRenderAstar.h"

void debugRenderSystem(const Context &ctx)
{
    debugRenderPlayer(ctx);
    debugRenderObjects(ctx);
    debugRenderNpc(ctx);
    debugRenderEffect(ctx);
    debugRenderAstar(ctx);
}
