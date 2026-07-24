#include "MonsterMeleeAttack.h"
#include "AreColBoxesNear.h"
#include "PrepareMonsterAttack.h"
#include "SelectAttackingMonsterIfPlayerHasNoSelection.h"
#include "SetMonsterFacingTowardTarget.h"
#include "../../../../structs/core/AnimationState.h"
#include "../../../../structs/core/constants/NpcMonsterConstants.h"
#include "../../../../structs/equipment/WeaponType.h"
#include "../SetNpcAiStatePursueTarget.h"

void monsterMeleeAttack(Context &ctx, uint32_t n)
{
    EntityType targetType;
    int targetId;
    SDL_FRect targetCol;
    if (!prepareMonsterAttack(ctx, n, targetType, targetId, targetCol))
        return;

    if (!areColBoxesNear(ctx, n, targetCol, NPC_MELEE_ATTACK_REACH))
    {
        setNpcAiStatePursueTarget(ctx, n);
        return;
    }

    auto &npc = ctx.data.npc;
    if (npc.equipment.weapon.type[n] != WeaponType::Melee)
        return;

    setMonsterFacingTowardTarget(ctx, n, targetCol);

    npc.autoAttack.attackTimer[n] = NPC_MELEE_AUTO_ATTACK_DELAY;
    npc.equipment.weapon.base.animation.animationState[n] = AnimationState::Starting;
    selectAttackingMonsterIfPlayerHasNoSelection(
        ctx,
        n,
        targetType,
        targetId);
}
