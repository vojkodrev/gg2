#include "FillRenderBufferSystem.h"
#include "FillPlayerRenderBuffer.h"
#include "FillNpcRenderBuffer.h"
#include "FillObjectRenderBuffer.h"
#include "SortRenderBuffer.h"

void FillRenderBufferSystem(Context &ctx)
{
    ctx.renderBuffer.count = 0;
    FillPlayerRenderBuffer(ctx);
    FillNpcRenderBuffer(ctx);
    FillObjectRenderBuffer(ctx);
    SortRenderBuffer(ctx);
}
