#include "FillRenderBufferSystem.h"
#include "ProjectAndCompactVisibleRenderEntries.h"
#include "FillActionBarRenderBuffer.h"
#include "FillPlayerRenderBuffer.h"
#include "FillNpcRenderBuffer.h"
#include "FillObjectRenderBuffer.h"
#include "FillEffectRenderBuffer.h"
#include "SortRenderBuffer.h"

void fillRenderBufferSystem(Context &ctx)
{
    ctx.renderBuffer.count = 0;
    
    fillPlayerRenderBuffer(ctx);
    fillNpcRenderBuffer(ctx);
    fillObjectRenderBuffer(ctx);
    fillEffectRenderBuffer(ctx);
    fillActionBarRenderBuffer(ctx);

    projectAndCompactVisibleRenderEntries(ctx);
    sortRenderBuffer(ctx);
}
