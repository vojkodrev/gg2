#include "FillObjectRenderBuffer.h"
#include "FillEntityBaseRenderBuffer.h"

void fillObjectRenderBuffer(Context &ctx)
{
    auto &rb = ctx.renderBuffer;
    auto &object = ctx.data.object;
    for (uint32_t objectIndex = 0;
        objectIndex < object.objectCount;
        objectIndex++)
    {
        fillEntityBaseRenderBuffer(
            rb,
            object.base,
            objectIndex,
            object.group.id[objectIndex],
            object.zIndex[objectIndex]);
    }
}
