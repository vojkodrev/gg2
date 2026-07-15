#pragma once

#include "../../../structs/core/Context.h"
#include "../../../structs/core/EntityType.h"
#include "../../../structs/core/constants/IndexConstants.h"
#include "NpcMonsterConstants.h"
#include "../SetNpcAiStatePursueTarget.h"
#include "../../attacks/aggroTable/AddToAggroTableValue.h"
#include "../../../utils/collision/DistToEntity.h"

inline bool detectTargetAndPursue(uint32_t n, Context &ctx)
{
    const int petId = ctx.data.player.petId;

    if (distToEntity(ctx, n, EntityType::Player, 0) < NPC_DETECT_RADIUS)
    {
        addToAggroTableValue(
            ctx.data.npc.aggroTable,
            n,
            EntityType::Player,
            0,
            0.0f);
        setNpcAiStatePursueTarget(n, ctx);
        return true;
    }
    else if (
        petId != INVALID_ID &&
        ctx.data.npc.active[petId] &&
        distToEntity(ctx, n, EntityType::NPC, petId) < NPC_DETECT_RADIUS)
    {
        addToAggroTableValue(
            ctx.data.npc.aggroTable,
            n,
            EntityType::NPC,
            petId,
            0.0f);
        setNpcAiStatePursueTarget(n, ctx);
        return true;
    }

    return false;
}
