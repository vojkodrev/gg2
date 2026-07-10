#pragma once

#include "../../../structs/core/Context.h"
#include "../../../structs/core/EntityType.h"
#include "NpcMonsterConstants.h"
#include "SetNpcAiStatePursueTarget.h"
#include "../../../utils/collision/DistToEntity.h"

inline bool detectTargetAndPursue(uint32_t n, Context &ctx)
{
    if (distToEntity(ctx, n, EntityType::Player, 0) >= NPC_DETECT_RADIUS)
        return false;

    setNpcAiStatePursueTarget(n, ctx, EntityType::Player, 0);
    return true;
}
