#include "FillActionBarRenderBuffer.h"
#include "FillEntityBaseRenderBuffer.h"

void fillActionBarRenderBuffer(Context &ctx)
{
    auto &actionBar = ctx.data.actionBar;
    fillEntityBaseRenderBuffer(ctx.renderBuffer, actionBar.rangedAutoAttack.base, 0, 0, 0);
    fillEntityBaseRenderBuffer(ctx.renderBuffer, actionBar.petAutoAttack.base, 0, 0, 0);
    fillEntityBaseRenderBuffer(ctx.renderBuffer, actionBar.petTaunt.base, 0, 0, 0);
    fillEntityBaseRenderBuffer(ctx.renderBuffer, actionBar.serpentSting.base, 0, 0, 0);
    fillEntityBaseRenderBuffer(ctx.renderBuffer, actionBar.concussiveShot.base, 0, 0, 0);
}
