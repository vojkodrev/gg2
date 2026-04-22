#include "FillRenderBufferSystem.h"
#include "FillPlayerRenderBuffer.h"
#include "FillNpcRenderBuffer.h"
#include "FillObjectRenderBuffer.h"
#include "SortRenderBuffer.h"

void fillRenderBufferSystem(Context &ctx)
{
    ctx.renderBuffer.count = 0;
    fillPlayerRenderBuffer(ctx);
    fillNpcRenderBuffer(ctx);
    fillObjectRenderBuffer(ctx);
    sortRenderBuffer(ctx);
}
