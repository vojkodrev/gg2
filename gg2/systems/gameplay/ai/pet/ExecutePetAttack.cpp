#include "ExecutePetAttack.h"
#include "../../../structs/core/constants/IndexConstants.h"
#include "NpcMonsterConstants.h"
#include "../../../structs/effect/DestroyEffectType.h"
#include "../../../structs/effect/EffectType.h"
#include "../../../utils/entity/CopyEntityBaseSlot.h"
#include "../../attacks/ApplyAttackDamage.h"
#include "../../attacks/aggroTable/AddToAggroTableValue.h"
#include "../../effects/EffectAlloc.h"

void executePetAttack(Context &ctx, uint32_t n, EntityType targetType, int targetId)
{
    const int targetGroupId = ctx.data.npc.group.id[targetId];

    const int effectIndex = effectAlloc(ctx.data.effect, ctx.data.groups, targetGroupId);
    if (effectIndex == INVALID_ID)
        return;

    const int damage = applyAttackDamage(
        ctx,
        EntityType::NPC,
        targetId,
        ctx.data.npc.statistics,
        ctx.data.npc.group,
        ctx.data.npc.base,
        PET_DAMAGE,
        PET_DAMAGE_RANDOM_RANGE);

    addToAggroTableValue(
        ctx.data.npc.aggroTable,
        targetId,
        EntityType::NPC,
        (int)n,
        (float)damage);

    copyEntityBaseSlot(
        ctx.data.effectTemplate.base,
        ctx.data.effectTemplate.bloodSplatterIndex,
        ctx.data.effect.base,
        effectIndex);
    ctx.data.effect.base.animation.animationStartTime[effectIndex] = ctx.frame.now;

    ctx.data.effect.type[effectIndex] = EffectType::AttachedToEntity;
    ctx.data.effect.destroyType[effectIndex] = DestroyEffectType::AnimationEnd;
    ctx.data.effect.destroyTimer[effectIndex] = 0.0f;
    ctx.data.effect.parent.type[effectIndex] = targetType;
    ctx.data.effect.parent.id[effectIndex] = targetId;
    ctx.data.npc.autoAttack.attackTimer[n] = PET_MELEE_AUTO_ATTACK_DELAY;
}
