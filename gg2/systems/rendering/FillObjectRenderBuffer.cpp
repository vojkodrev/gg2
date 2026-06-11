#include "FillObjectRenderBuffer.h"
#include "FillEntityBaseRenderBuffer.h"
#include "../../structs/core/constants/RenderConstants.h"

void fillObjectRenderBuffer(Context &ctx)
{
    auto &rb = ctx.renderBuffer;
    auto &object = ctx.data.object;
    for (uint32_t i = 0; i < object.objectCount; i++)
    {
        fillEntityBaseRenderBuffer(
            rb,
            object.base,
            i,
            object.groupId[i],
            PARENT_Z_INDEX);
    }
}
