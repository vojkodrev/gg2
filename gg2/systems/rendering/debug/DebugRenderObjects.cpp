#include "DebugRenderObjects.h"
#include "RenderColBox.h"
#include "../../../utils/collision/EntityColAABBObject.h"

void debugRenderObjects(const Context &ctx)
{
    if (!ctx.data.debug.showCollision)
        return;

    for (uint32_t i = 0; i < ctx.data.object.objectCount; i++)
        renderColBox(ctx, entityColAABB(ctx.data.object, i));
}
