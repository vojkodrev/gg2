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

        const int zIndex =
            effect.type[i] == EffectType::DamageNumber
                ? EFFECT_DAMAGE_NUMBER_Z_INDEX
                : EFFECT_Z_INDEX;

        fillEntityBaseRenderBuffer(
            rb,
            effect.base,
            i,
            effect.groupId[i],
            zIndex);
    }
}
