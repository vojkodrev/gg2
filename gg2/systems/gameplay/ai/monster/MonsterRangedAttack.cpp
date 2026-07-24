#include "MonsterRangedAttack.h"
#include "IsMonsterRangedAttackTargetTooClose.h"
#include "IsMonsterRangedTargetVisible.h"
#include "PrepareMonsterAttack.h"
#include "SelectAttackingMonsterIfPlayerHasNoSelection.h"
#include "SetMonsterFacingTowardTarget.h"
#include "../../../../structs/core/constants/IndexConstants.h"
#include "../../../../structs/core/constants/NpcMonsterConstants.h"
#include "../../../../structs/core/constants/TintConstants.h"
#include "../../../../structs/effect/ProjectileType.h"
#include "../../../../structs/equipment/WeaponType.h"
#include "../../projectile/CreateTargetedProjectileEffect.h"
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

    const SDL_FColor tint = {
        CLEAR_TINT_R,
        CLEAR_TINT_G,
        CLEAR_TINT_B,
        CLEAR_TINT_A
    };
    const int effectIndex = createTargetedProjectileEffect(
        ctx,
        EntityType::NPC,
        static_cast<int>(n),
        targetType,
        targetId,
        ProjectileType::AutoAttack,
        tint);
    if (effectIndex == INVALID_ID)
        return;

    npc.autoAttack.attackTimer[n] = NPC_RANGED_AUTO_ATTACK_DELAY;
    npc.equipment.weapon.showAmmo[n] = false;
    selectAttackingMonsterIfPlayerHasNoSelection(
        ctx,
        n,
        targetType,
        targetId);
}
