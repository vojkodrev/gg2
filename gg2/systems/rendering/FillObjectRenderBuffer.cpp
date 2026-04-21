#include "FillObjectRenderBuffer.h"

void FillObjectRenderBuffer(Context &ctx)
{
    auto &rb = ctx.renderBuffer;
    auto &object = ctx.data.object;
    for (uint32_t i = 0; i < object.objectCount; i++)
    {
        uint32_t n = rb.count++;
        rb.src.x[n] = (float)object.src.x[i];
        rb.src.y[n] = (float)object.src.y[i];
        rb.src.w[n] = (float)object.src.w[i];
        rb.src.h[n] = (float)object.src.h[i];
        rb.dst.x[n] = object.position.x[i];
        rb.dst.y[n] = object.position.y[i];
        rb.dst.w[n] = object.position.w[i];
        rb.dst.h[n] = object.position.h[i];
        rb.dst.colOffY[n] = object.collision.offY[i];
    }
}
