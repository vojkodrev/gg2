#pragma once
#include "../../../structs/core/Context.h"
#include "../../../structs/core/constants/FontConstants.h"
#include "../../../structs/core/constants/TintConstants.h"
#include "../../../structs/effect/DestroyEffectType.h"
#include "../../../structs/effect/EffectType.h"
#include "../../../structs/effect/ParentType.h"
#include "../../../utils/collision/EntityColAABB.h"
#include "../../../utils/collision/EntityColCenter.h"
#include "../../../utils/entity/CopyEntityBaseSlot.h"
#include "EffectAlloc.h"
#include <algorithm>
#include <string>

inline void spawnTextEffect(
    Context &ctx,
    uint32_t npcIndex,
    const std::string &text)
{
    const auto &templateBase = ctx.data.effectTemplate.base;
    const SDL_FPoint npcColCenter = entityColCenter(entityColAABB(ctx.data.npc.base, npcIndex));
    const float totalW =
        text.size() * FONT_GLYPH_W +
        std::max<int>(0, static_cast<int>(text.size()) - 1) * DAMAGE_NUMBER_DIGIT_SEPARATOR;
    const float startX = npcColCenter.x - totalW * 0.5f;
    const float posY =
        ctx.data.npc.base.position.y[npcIndex] -
        FONT_GLYPH_H -
        DAMAGE_NUMBER_DISTANCE_FROM_ENTITY;

    for (uint32_t i = 0; i < text.size(); i++)
    {
        const unsigned char glyph = static_cast<unsigned char>(text[i]);
        const int effectIndex = effectAlloc(ctx.data.effect, ctx.data.groups, ctx.data.npc.groupId[npcIndex]);
        if (effectIndex == -1)
            return;

        copyEntityBaseSlot(
            templateBase,
            ctx.data.effectTemplate.fontOffset + glyph,
            ctx.data.effect.base,
            effectIndex);

        ctx.data.effect.type[effectIndex] = EffectType::DamageNumber;
        ctx.data.effect.destroyType[effectIndex] = DestroyEffectType::Timer;
        ctx.data.effect.destroyTimer[effectIndex] = DAMAGE_NUMBER_DESTROY_TIME;
        ctx.data.effect.parent.type[effectIndex] = ParentType::NPC;
        ctx.data.effect.parent.id[effectIndex] = npcIndex;
        ctx.data.effect.base.position.x[effectIndex] =
            startX + i * (FONT_GLYPH_W + DAMAGE_NUMBER_DIGIT_SEPARATOR);
        ctx.data.effect.base.position.y[effectIndex] = posY;
        ctx.data.effect.base.tint.r[effectIndex] = DAMAGE_NUMBER_TINT_R;
        ctx.data.effect.base.tint.g[effectIndex] = DAMAGE_NUMBER_TINT_G;
        ctx.data.effect.base.tint.b[effectIndex] = DAMAGE_NUMBER_TINT_B;
        ctx.data.effect.base.tint.a[effectIndex] = DAMAGE_NUMBER_TINT_A;
    }
}
