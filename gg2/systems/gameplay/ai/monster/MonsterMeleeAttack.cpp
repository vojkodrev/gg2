#include "MonsterMeleeAttack.h"
#include "AreColBoxesNear.h"
#include "GetEntityColAABB.h"
#include "../../../../structs/core/AnimationState.h"
#include "../../../../structs/core/EntityType.h"
#include "../../../../structs/core/constants/NpcMonsterConstants.h"
#include "../../../../structs/equipment/WeaponType.h"
#include "SetNpcAiStateReturnToSpawn.h"
#include "../SetNpcAiStatePursueTarget.h"
#include "../../attacks/aggroTable/ClearInactiveAggroTableEntitiesIfMaxInactive.h"

void monsterMeleeAttack(Context &ctx, uint32_t n)
{
    if (ctx.data.npc.ai.attackedTimer[n] <= 0.0f)
    {
        setNpcAiStateReturnToSpawn(n, ctx);
        return;
    }

    const auto &target = ctx.data.npc.ai.target;
    auto &aggroTable = ctx.data.npc.aggroTable;
    clearInactiveAggroTableEntitiesIfMaxInactive(
        aggroTable,
        n,
        ctx.data.npc.active);

    if (aggroTable.pool.count[n] == 0)
    {
        setNpcAiStateReturnToSpawn(n, ctx);
        return;
    }

    if (target.type[n] != aggroTable.maxEntityType[n] ||
        target.id[n] != aggroTable.maxEntityId[n])
    {
        setNpcAiStatePursueTarget(ctx, n);
        return;
    }

    const EntityType targetType = target.type[n];
    const int targetId = target.id[n];
    if (targetType != EntityType::Player && targetType != EntityType::NPC)
    {
        setNpcAiStateReturnToSpawn(n, ctx);
        return;
    }
    if (targetType == EntityType::NPC && !ctx.data.npc.active[targetId])
    {
        setNpcAiStateReturnToSpawn(n, ctx);
        return;
    }
    const SDL_FRect targetCol = getEntityColAABB(ctx, targetType, targetId);
    if (!areColBoxesNear(ctx, n, targetCol, NPC_ATTACK_REACH))
    {
        setNpcAiStatePursueTarget(ctx, n);
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
