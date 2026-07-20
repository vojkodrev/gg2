#pragma once
#include "Context.h"
#include "EntityType.h"
#include "IndexConstants.h"
#include "astar/FollowAStarPathTo.h"
#include <cstdint>

inline void followMonsterPursueTarget(
    Context &ctx,
    uint32_t n,
    EntityType targetType,
    int targetId,
    const SDL_FRect &targetCol)
{
    const int targetNpcIndex = targetType == EntityType::NPC ? targetId : INVALID_ID;
    followAStarPathTo(n, ctx, targetCol, targetNpcIndex);
}
