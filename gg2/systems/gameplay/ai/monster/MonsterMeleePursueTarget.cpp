#include "MonsterMeleePursueTarget.h"
#include "../../../structs/core/constants/IndexConstants.h"
#include "AreColBoxesNear.h"
#include "GetEntityColAABB.h"
#include "NpcMonsterConstants.h"
#include "astar/FollowAStarPathTo.h"
#include "SetNpcAiStateReturnToSpawn.h"
#include "SetNpcAiStateAttack.h"
#include "SetNpcAiTarget.h"
#include "../../attacks/aggroTable/ClearInactiveAggroTableEntitiesIfMaxInactive.h"
#include "../../../structs/core/EntityType.h"

void monsterMeleePursueTarget(Context &ctx, uint32_t n)
{
    if (ctx.data.npc.ai.attackedTimer[n] <= 0.0f)
    {
        setNpcAiStateReturnToSpawn(n, ctx);
        return;
    }

    auto &target = ctx.data.npc.ai.target;
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
        setNpcAiTarget(
            n,
            ctx,
            aggroTable.maxEntityType[n],
            aggroTable.maxEntityId[n]);
    }

    const EntityType targetType = target.type[n];
    const int targetId = target.id[n];
    if (targetType != EntityType::Player && targetType != EntityType::NPC)
    {
        setNpcAiStateReturnToSpawn(n, ctx);
        return;
    }
    const SDL_FRect targetCol = getEntityColAABB(ctx, targetType, targetId);

    if (areColBoxesNear(ctx, n, targetCol, NPC_ATTACK_REACH))
    {
        setNpcAiStateAttack(n, ctx);
        return;
    }

    const int targetNpcIndex = targetType == EntityType::NPC ? targetId : INVALID_ID;
    followAStarPathTo(n, ctx, targetCol, targetNpcIndex);
}
