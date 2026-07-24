#include "MonsterRangedAttack.h"
#include "IsMonsterRangedAttackTargetTooClose.h"
#include "IsMonsterRangedTargetVisible.h"
#include "PrepareMonsterAttack.h"
#include "SelectAttackingMonsterIfPlayerHasNoSelection.h"
#include "SetMonsterFacingTowardTarget.h"
#include "../../../../structs/core/constants/NpcMonsterConstants.h"
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
    if (npc.equipment.weapon.type[n] != WeaponType::Ranged ||
        !npc.equipment.weapon.showAmmo[n])
        return;

    if (isMonsterRangedAttackTargetTooClose(ctx, n, targetType, targetId))
        return;

    if (!isMonsterRangedTargetVisible(
            ctx,
            n,
            targetCol))
    {
        setNpcAiStatePursueTarget(ctx, n);
        return;
    }

    setMonsterFacingTowardTarget(ctx, n, targetCol);

    bool attackExecuted = tryExecuteConcussiveShot(
        ctx,
        EntityType::NPC,
        static_cast<int>(n),
        targetType,
        targetId);

    attackExecuted = tryExecuteRangedAutoAttack(
        ctx,
        EntityType::NPC,
        static_cast<int>(n),
        targetType,
        targetId,
        npc.autoAttack,
        npc.equipment.weapon,
        NPC_RANGED_AUTO_ATTACK_DELAY) || attackExecuted;
    if (!attackExecuted)
        return;

    selectAttackingMonsterIfPlayerHasNoSelection(
        ctx,
        n,
        targetType,
        targetId);
}
