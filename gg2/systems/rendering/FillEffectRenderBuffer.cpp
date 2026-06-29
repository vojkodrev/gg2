#include "FillEffectRenderBuffer.h"
#include "FillEntityBaseRenderBuffer.h"
#include "../../structs/core/constants/RenderConstants.h"
#include "../../structs/effect/EffectType.h"

void fillEffectRenderBuffer(Context &ctx)
{
    auto &rb = ctx.renderBuffer;
    auto &effect = ctx.data.effect;
    for (uint32_t i = 0; i < effect.pool.count; i++)
    {
        if (!effect.pool.active[i])
            continue;

        int zIndex = EFFECT_Z_INDEX;
        if (effect.type[i] == EffectType::Digit)
            zIndex = EFFECT_DIGIT_Z_INDEX;

        fillEntityBaseRenderBuffer(
            rb,
            effect.base,
            i,
            effect.groupId[i],
            zIndex);
    }
}
