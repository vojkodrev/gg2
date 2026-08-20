#pragma once
#include "../../../structs/core/Context.h"
#include "../../../structs/core/constants/IndexConstants.h"
#include "../../../structs/effect/DestroyEffectType.h"
#include "../../../utils/entity/CopyEntityBaseSlot.h"

template<int N>
inline void copyEffect(
    Context &ctx,
    const EntityBase<N> &source,
    int sourceIndex,
    int effectIndex)
{
    auto &effect = ctx.data.effect;
    copyEntityBaseSlot(source, sourceIndex, effect.base, effectIndex);
    effect.base.animation.animationStartTime[effectIndex] = ctx.frame.now;

    effect.type[effectIndex] = EffectType::None;
    effect.projectileType[effectIndex] = ProjectileType::None;
    effect.destroyType[effectIndex] = DestroyEffectType::None;
    effect.destroyTimer[effectIndex] = 0.0f;
    effect.parent.type[effectIndex] = EntityType::None;
    effect.parent.id[effectIndex] = INVALID_ID;
    effect.target.type[effectIndex] = EntityType::None;
    effect.target.id[effectIndex] = INVALID_ID;
}
