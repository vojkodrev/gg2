#include "MonsterAttack.h"
#include "AreColBoxesNear.h"
#include "GetEntityColAABB.h"
#include "../../../../structs/core/AnimationState.h"
#include "../../../../structs/core/constants/NpcMonsterConstants.h"
#include "../../../../structs/equipment/WeaponType.h"
#include "SetNpcAiStateReturnToSpawn.h"
#include "SetNpcAiStatePursueTarget.h"
#include "CanMonsterAttackTarget.h"

void monsterAttack(uint32_t n, Context &ctx)
{
    if (ctx.data.npc.ai.attackedTimer[n] <= 0.0f)
    {
        setNpcAiStateReturnToSpawn(n, ctx);
        return;
    }
    const auto &target = ctx.data.npc.ai.target;
    if (!canMonsterAttackTarget(target.type[n]))
        return;
    const SDL_FRect targetCol = getEntityColAABB(ctx, target.type[n], target.id[n]);
    if (!areColBoxesNear(ctx, n, targetCol, NPC_ATTACK_REACH))
    {
        setNpcAiStatePursueTarget(n, ctx, target.type[n], target.id[n]);
        return;
    }

    auto &npc = ctx.data.npc;
    if (npc.equipment.weapon.type[n] != WeaponType::Melee)
        return;

    if (npc.autoAttack.attackTimer[n] > 0.0f)
        return;

    npc.autoAttack.attackTimer[n] = NPC_MELEE_AUTO_ATTACK_DELAY;
    npc.equipment.weapon.base.animation.animationState[n] = AnimationState::Starting;
}
