#pragma once
#include "Context.h"
#include "../../../structs/entity/EntityType.h"
#include "../../../structs/core/constants/AttackConstants.h"
#include "../../../utils/collision/DistToEntity.h"
#include <cstdint>

inline bool isRangedAttackTargetTooClose(
    Context &ctx,
    uint32_t npcIndex,
    EntityType targetType,
    int targetId)
{
    return distToEntity(ctx, npcIndex, targetType, targetId) <
        RANGED_ATTACK_MIN_DISTANCE;
}
