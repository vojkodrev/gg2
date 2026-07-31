#include "MonsterRangedAttack.h"
#include "RetreatRangedMonster.h"
#include "IsMonsterRangedAttackTargetTooClose.h"
#include "IsMonsterRangedTargetVisible.h"
#include "PrepareMonsterAttack.h"
#include "SelectAttackingMonsterIfPlayerHasNoSelection.h"
#include "SetMonsterFacingTowardTarget.h"
#include "../../../../structs/core/constants/ConcussiveShotConstants.h"
#include "../../../../structs/equipment/WeaponType.h"
#include "../../attacks/TryExecuteConcussiveShot.h"
#include "../../attacks/TryExecuteRangedAutoAttack.h"
#include "../SetNpcAiStatePursueTarget.h"

void monsterRangedAttack(Context &ctx, uint32_t n)
{
    EntityType targetType;
    int targetId;
    SDL_FRect targetCol;
    if (!prepareMonsterAttack(ctx, n, targetType, targetId, targetCol))
        return;

    auto &npc = ctx.data.npc;
    if (npc.equipment.weapon.type[n] != WeaponType::Ranged)
        return;

    if (!retreatRangedMonster(
            ctx,
            n,
            targetType,
            targetId,
            targetCol))
        return;

    if (!isMonsterRangedTargetVisible(
            ctx,
            n,
            targetCol))
    {
        setNpcAiStatePursueTarget(ctx, n);
        return;
    }

    if (isMonsterRangedAttackTargetTooClose(
            ctx,
            n,
            targetType,
            targetId))
        return;

    setMonsterFacingTowardTarget(ctx, n, targetCol);

    bool rangedAutoAttackExecuted = false;
    if (npc.ai.rangedAttackStaggerTimer[n] <= 0.0f &&
        npc.autoAttack.attackTimer[n] <= 0.0f)
    {
        rangedAutoAttackExecuted = tryExecuteRangedAutoAttack(
            ctx,
            EntityType::NPC,
            static_cast<int>(n),
            targetType,
            targetId,
            npc.autoAttack,
            npc.equipment.weapon,
            NPC_RANGED_AUTO_ATTACK_DELAY);
        if (rangedAutoAttackExecuted)
            npc.ai.rangedAttackStaggerTimer[n] =
                NPC_RANGED_ATTACK_STAGGER_TIME;
    }

    bool concussiveShotExecuted = false;
    if (npc.ai.rangedAttackStaggerTimer[n] <= 0.0f)
    {
        concussiveShotExecuted = tryExecuteConcussiveShot(
            ctx,
            EntityType::NPC,
            static_cast<int>(n),
            targetType,
            targetId,
            npc.concussiveShotCooldownTimer[n],
            npc.globalCooldownTimer[n],
            npc.statistics.mana,
            npc.equipment.weapon,
            CONCUSSIVE_SHOT_PROJECTILE_OFFSET);
        if (concussiveShotExecuted)
            npc.ai.rangedAttackStaggerTimer[n] =
                NPC_RANGED_ATTACK_STAGGER_TIME;
    }
    if (!rangedAutoAttackExecuted && !concussiveShotExecuted)
        return;

    selectAttackingMonsterIfPlayerHasNoSelection(
        ctx,
        n,
        targetType,
        targetId);
}
