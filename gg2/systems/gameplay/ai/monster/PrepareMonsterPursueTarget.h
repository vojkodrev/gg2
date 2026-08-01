#pragma once
#include "Context.h"
#include "EntityType.h"
#include "GetEntityColAABB.h"
#include "NpcConstants.h"
#include "SetNpcAiStateReturnToSpawn.h"
#include "SetNpcAiTarget.h"
#include "../../attacks/aggroTable/ClearInactiveAggroTableEntitiesIfMaxInactive.h"
#include <cstdint>

inline bool prepareMonsterPursueTarget(
    Context &ctx,
    uint32_t n,
    EntityType &targetType,
    int &targetId,
    SDL_FRect &targetCol)
{
    auto &npc = ctx.data.npc;
    if (npc.ai.attackedTimer[n] <= 0.0f)
    {
        setNpcAiStateReturnToSpawn(n, ctx);
        return false;
    }

    auto &aggroTable = npc.aggroTable;
    clearInactiveAggroTableEntitiesIfMaxInactive(aggroTable, n, npc.active);
    if (aggroTable.pool.count[n] == 0)
    {
        setNpcAiStateReturnToSpawn(n, ctx);
        return false;
    }

    auto &target = npc.ai.target;
    if (target.type[n] != aggroTable.maxEntityType[n] ||
        target.id[n] != aggroTable.maxEntityId[n])
    {
        setNpcAiTarget(
            n,
            ctx,
            aggroTable.maxEntityType[n],
            aggroTable.maxEntityId[n]);
        npc.ai.targetVisibleTimer[n] = 0.0f;
        npc.ai.rangedAttackTargetTooCloseCheckTimer[n] = 0.0f;
        npc.ai.targetTooClose[n] = false;
        npc.ai.retreating[n] = false;
        npc.ai.rangedRetreatPointCheckTimer[n] = 0.0f;
    }

    targetType = target.type[n];
    targetId = target.id[n];
    const bool playerTargetIsValid =
        targetType == EntityType::Player && targetId == 0;
    const bool npcTargetIsValid =
        targetType == EntityType::NPC &&
        targetId >= 0 &&
        targetId < MAX_NPCS &&
        npc.active[targetId];
    if (!playerTargetIsValid && !npcTargetIsValid)
    {
        setNpcAiStateReturnToSpawn(n, ctx);
        return false;
    }

    targetCol = getEntityColAABB(ctx, targetType, targetId);
    return true;
}
