#include "DebugRenderObjects.h"
#include "DebugRenderEntityBase.h"

void debugRenderObjects(const Context &ctx)
{
    if (!ctx.data.debug.showCollision)
        return;

    for (uint32_t i = 0; i < ctx.data.object.objectCount; i++)
        debugRenderEntityBase(ctx, ctx.data.object.base, i, SDL_Color{255, 0, 0, 255});
}
