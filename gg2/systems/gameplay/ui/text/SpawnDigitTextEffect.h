#pragma once
#include "../../../../structs/core/Context.h"
#include "../../../../structs/core/EntityType.h"
#include "../../../../structs/core/constants/FontConstants.h"
#include "../../../../structs/core/constants/TintConstants.h"
#include "../../../../structs/effect/DestroyEffectType.h"
#include "../../../../structs/effect/EffectType.h"
#include "../../../../utils/entity/CopyEntityBaseSlot.h"
#include "../../effects/EffectAlloc.h"
#include <SDL3/SDL.h>
#include <algorithm>
#include <string>

inline void spawnDigitTextEffect(
    Context &ctx,
    int groupId,
    EntityType parentType,
    int parentId,
    DestroyEffectType destroyType,
    float destroyTimer,
    const std::string &text,
    SDL_FPoint pos,
    SDL_FColor tint)
{
    const auto &templateBase = ctx.data.effectTemplate.base;
    const float totalW =
        text.size() * FONT_GLYPH_W +
        std::max<int>(0, static_cast<int>(text.size()) - 1) * DAMAGE_NUMBER_DIGIT_SEPARATOR;
    const float startX = pos.x - totalW * 0.5f;

    for (uint32_t i = 0; i < text.size(); i++)
    {
        const unsigned char glyph = static_cast<unsigned char>(text[i]);
        const int effectIndex = effectAlloc(ctx.data.effect, ctx.data.groups, groupId);
        if (effectIndex == -1)
            return;

        copyEntityBaseSlot(
            templateBase,
            ctx.data.effectTemplate.fontOffset + glyph,
            ctx.data.effect.base,
            effectIndex);

        ctx.data.effect.type[effectIndex] = EffectType::Digit;
        ctx.data.effect.destroyType[effectIndex] = destroyType;
        ctx.data.effect.destroyTimer[effectIndex] = destroyTimer;
        ctx.data.effect.parent.type[effectIndex] = parentType;
        ctx.data.effect.parent.id[effectIndex] = parentId;
        ctx.data.effect.base.position.x[effectIndex] =
            startX + i * (FONT_GLYPH_W + DAMAGE_NUMBER_DIGIT_SEPARATOR);
        ctx.data.effect.base.position.y[effectIndex] = pos.y;
        ctx.data.effect.base.position.absolute[effectIndex] = parentType == EntityType::ActionBarIcon;
        ctx.data.effect.base.tint.r[effectIndex] = tint.r;
        ctx.data.effect.base.tint.g[effectIndex] = tint.g;
        ctx.data.effect.base.tint.b[effectIndex] = tint.b;
        ctx.data.effect.base.tint.a[effectIndex] = tint.a;
    }
}
