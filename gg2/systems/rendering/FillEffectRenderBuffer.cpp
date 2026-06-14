#include "FillEffectRenderBuffer.h"
#include "FillEntityBaseRenderBuffer.h"
#include "../../structs/core/constants/RenderConstants.h"

void fillEffectRenderBuffer(Context &ctx)
{
    auto &rb = ctx.renderBuffer;
    auto &effect = ctx.data.effect;
    for (uint32_t i = 0; i < effect.pool.count; i++)
    {
        if (!effect.pool.active[i])
            continue;

        fillEntityBaseRenderBuffer(
            rb,
            effect.base,
            i,
            effect.groupId[i],
            EFFECT_Z_INDEX);
    }
}
