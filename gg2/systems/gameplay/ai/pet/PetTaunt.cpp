#include "PetTaunt.h"
#include "../../../structs/core/constants/IndexConstants.h"
#include "../../../structs/effect/DestroyEffectType.h"
#include "../../../structs/effect/EffectType.h"
#include "../../../utils/entity/CopyEntityBaseSlot.h"
#include "../../effects/EffectAlloc.h"

void petTaunt(uint32_t n, Context &ctx)
{
    const int targetId = ctx.data.npc.ai.target.id[n];

    const int targetGroupId = ctx.data.npc.group.id[targetId];
    const int effectIndex = effectAlloc(ctx.data.effect, ctx.data.groups, targetGroupId);
    if (effectIndex == INVALID_ID)
        return;

    copyEntityBaseSlot(
        ctx.data.effectTemplate.base,
        ctx.data.effectTemplate.tauntIndex,
        ctx.data.effect.base,
        effectIndex);
    ctx.data.effect.base.animation.animationStartTime[effectIndex] = ctx.frame.now;

    ctx.data.effect.type[effectIndex] = EffectType::Taunt;
    ctx.data.effect.destroyType[effectIndex] = DestroyEffectType::AnimationEnd;
    ctx.data.effect.destroyTimer[effectIndex] = 0.0f;
    ctx.data.effect.parent.type[effectIndex] = EntityType::NPC;
    ctx.data.effect.parent.id[effectIndex] = targetId;
}
