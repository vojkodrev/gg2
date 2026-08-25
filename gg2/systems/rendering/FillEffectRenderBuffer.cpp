#include "FillEffectRenderBuffer.h"
#include "FillEntityBaseRenderBuffer.h"
#include "../../structs/core/constants/RenderConstants.h"
#include "../../structs/effect/EffectType.h"

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

        int zIndex = EFFECT_Z_INDEX;
        if (effect.type[effectIndex] == EffectType::FrostNova ||
            effect.type[effectIndex] == EffectType::ArcaneExplosion)
            zIndex = AOE_PARENT_SPELL_Z_INDEX;
        else if (effect.type[effectIndex] == EffectType::BloodSplatter)
            zIndex = EFFECT_BLOOD_SPLATTER_Z_INDEX;
        else if (effect.type[effectIndex] == EffectType::Taunt)
            zIndex = EFFECT_TAUNT_Z_INDEX;
        else if (effect.type[effectIndex] == EffectType::Character)
            zIndex = EFFECT_CHARACTER_Z_INDEX;

        fillEntityBaseRenderBuffer(
            rb,
            effect.base,
            effectIndex,
            effect.groupId[effectIndex],
            zIndex);
    }
}
