#include "FillObjectRenderBuffer.h"
#include "../../structs/core/constants/RenderConstants.h"

void fillObjectRenderBuffer(Context &ctx)
{
    auto &rb = ctx.renderBuffer;
    auto &object = ctx.data.object;
    for (uint32_t i = 0; i < object.objectCount; i++)
    {
        int f = object.base.animation.frameIndex[i];
        uint32_t n = rb.count++;
        rb.src.x[n] = (float)object.base.animation.frame.src.x[i][f];
        rb.src.y[n] = (float)object.base.animation.frame.src.y[i][f];
        rb.src.w[n] = (float)object.base.animation.frame.src.w[i][f];
        rb.src.h[n] = (float)object.base.animation.frame.src.h[i][f];
        rb.src.rotate[n] = 0.0f;
        rb.dst.x[n] = object.base.position.x[i];
        rb.dst.y[n] = object.base.position.y[i];
        rb.dst.w[n] = object.base.position.w[i];
        rb.dst.h[n] = object.base.position.h[i];
        rb.dst.sortY[n] = rb.dst.y[n] + object.base.animation.frame.collision.offY[i][f];
        rb.group.id[n] = object.groupId[i];
        rb.group.zIndex[n] = PARENT_Z_INDEX;
        rb.flipX[n] = false;
    }
}
