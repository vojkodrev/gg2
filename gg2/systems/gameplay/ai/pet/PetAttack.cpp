#include "PetAttack.h"
#include "../../../structs/core/constants/IndexConstants.h"
#include "AreColBoxesNear.h"
#include "GetEntityColAABB.h"
#include "NpcMonsterConstants.h"
#include "SetNpcAiStateIdle.h"
#include "SetNpcAiStatePursuingTarget.h"
#include "../../../structs/core/EntityType.h"
#include "../../../structs/effect/DestroyEffectType.h"
#include "../../../structs/effect/EffectType.h"
#include "../../../utils/entity/CopyEntityBaseSlot.h"
#include "../../attacks/ApplyAttackDamage.h"
#include "../../effects/EffectAlloc.h"

void petAttack(uint32_t n, Context &ctx)
{
    const auto &target = ctx.data.npc.ai.target;
    const EntityType targetType = target.type[n];
    const int targetId = target.id[n];

    if (targetType == EntityType::NPC && !ctx.data.npc.active[targetId])
    {
        setNpcAiStateIdle(n, ctx);
        return;
    }

    const SDL_FRect targetCol = getEntityColAABB(ctx, targetType, targetId);
    if (!areColBoxesNear(ctx, n, targetCol, NPC_ATTACK_REACH))
    {
        setNpcAiStatePursuingTarget(n, ctx, targetType, targetId);
        return;
    }

    if (ctx.data.npc.autoAttack.attackTimer[n] > 0.0f)
        return;

    const int targetGroupId = ctx.data.npc.group.id[targetId];

    const int effectIndex = effectAlloc(ctx.data.effect, ctx.data.groups, targetGroupId);
    if (effectIndex == INVALID_ID)
        return;

    applyAttackDamage(
        ctx,
        EntityType::NPC,
        targetId,
        ctx.data.npc.statistics,
        ctx.data.npc.group,
        ctx.data.npc.base,
        PET_DAMAGE,
        PET_DAMAGE_RANDOM_RANGE);

    copyEntityBaseSlot(
        ctx.data.effectTemplate.base,
        ctx.data.effectTemplate.bloodSplatterOffset,
        ctx.data.effect.base,
        effectIndex);
    ctx.data.effect.base.animation.animationStartTime[effectIndex] = ctx.frame.now;

    ctx.data.effect.type[effectIndex] = EffectType::BloodSplatter;
    ctx.data.effect.destroyType[effectIndex] = DestroyEffectType::AnimationEnd;
    ctx.data.effect.destroyTimer[effectIndex] = 0.0f;
    ctx.data.effect.parent.type[effectIndex] = targetType;
    ctx.data.effect.parent.id[effectIndex] = targetId;
    ctx.data.npc.autoAttack.attackTimer[n] = PET_MELEE_AUTO_ATTACK_DELAY;
}
