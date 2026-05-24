#include "DebugRenderSystem.h"
#include "DebugRenderPlayer.h"
#include "DebugRenderNpc.h"
#include "DebugRenderObjects.h"
#include "DebugRenderAstar.h"

void debugRenderSystem(const Context &ctx)
{
    debugRenderPlayer(ctx);
    debugRenderObjects(ctx);
    debugRenderNpc(ctx);
    debugRenderAstar(ctx);
}
