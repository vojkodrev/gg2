#pragma once
#include "Context.h"
#include "IsNpcTargetVisibleFrom.h"
#include "EntityColAABB.h"
#include "EntityColCenter.h"

inline bool isNpcTargetVisible(
    Context &ctx,
    uint32_t n,
    const SDL_FRect &targetCol)
{
    return isNpcTargetVisibleFrom(
        ctx,
        n,
        targetCol,
        entityColCenter(entityColAABB(ctx.data.npc.base, n)));
}
