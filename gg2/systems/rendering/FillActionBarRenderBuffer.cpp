#include "FillActionBarRenderBuffer.h"
#include "FillEntityBaseRenderBuffer.h"

void fillActionBarRenderBuffer(Context &ctx)
{
    auto &actionBar = ctx.data.actionBar;
    fillEntityBaseRenderBuffer(ctx.renderBuffer, actionBar.rangedAutoAttack.base, 0, 0, 0);
    fillEntityBaseRenderBuffer(ctx.renderBuffer, actionBar.serpentSting.base, 0, 0, 0);
}
