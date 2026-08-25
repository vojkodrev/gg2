#include "FillEffectRenderBuffer.h"
#include "FillEntityBaseRenderBuffer.h"

void fillEffectRenderBuffer(Context &ctx)
{
    auto &rb = ctx.renderBuffer;
    auto &effect = ctx.data.effect;
    for (uint32_t effectIndex = 0;
        effectIndex < effect.pool.count[0];
        effectIndex++)
    {
        if (!effect.pool.active[0][effectIndex])
            continue;

        fillEntityBaseRenderBuffer(
            rb,
            effect.base,
            effectIndex,
            effect.group.id[effectIndex],
            effect.zIndex[effectIndex]);
    }
}
