#pragma once
#include "Context.h"
#include "MainEntityColAABB.h"
#include "EntityColCenter.h"
#include "../../facing/SetFacingTowardX.h"
#include <cstdint>

inline void setMonsterFacingTowardTarget(
    Context &ctx,
    uint32_t n,
    const SDL_FRect &targetCol)
{
    auto &npc = ctx.data.npc;
    const float npcCenterX =
        entityColCenter(mainEntityColAABB(npc.base, n)).x;
    const float targetCenterX = entityColCenter(targetCol).x;
    setFacingTowardX(npc.base.facing, n, npcCenterX, targetCenterX);
}
