#include "DebugRenderObjects.h"
#include "RenderColBox.h"
#include "../../../utils/collision/EntityColAABB.h"

void debugRenderObjects(const Context &ctx)
{
    if (!ctx.data.debug.showCollision)
        return;

    SDL_SetRenderDrawColor(ctx.renderer, 255, 0, 0, 255);
    for (uint32_t i = 0; i < ctx.data.object.objectCount; i++)
        renderColBox(ctx, entityColAABB(ctx.data.object.base, i));
}
