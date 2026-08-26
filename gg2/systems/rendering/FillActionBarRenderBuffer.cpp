#include "FillActionBarRenderBuffer.h"
#include "FillEntityBaseRenderBuffer.h"

void fillActionBarRenderBuffer(Context &ctx)
{
    auto &actionBar = ctx.data.actionBar;
    auto &base = actionBar.icon.base;
    for (int iconIndex = 0; iconIndex < MAX_ACTION_BAR_ICONS; iconIndex++)
    {
        if (!actionBar.icon.active[iconIndex])
            continue;
        fillEntityBaseRenderBuffer(
            ctx.renderBuffer,
            base,
            iconIndex,
            actionBar.groupId,
            actionBar.icon.zIndex[iconIndex]);
    }
}
