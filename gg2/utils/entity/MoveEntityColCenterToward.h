#pragma once
#include "../../structs/core/Context.h"
#include "../collision/EntityColAABB.h"
#include "../collision/EntityColCenter.h"
#include <cstdint>
#include <cmath>

template<int N>
inline void moveEntityColCenterToward(
    Context &ctx,
    EntityBase<N> &base,
    uint32_t index,
    SDL_FPoint target,
    float speed)
{
    const float dt = ctx.frame.dt;
    const SDL_FRect col = entityColAABB(base, index);
    const SDL_FPoint colCenter = entityColCenter(col);
    const float dx = target.x - colCenter.x;
    const float dy = target.y - colCenter.y;
    const float d = sqrtf(dx * dx + dy * dy);
    if (d == 0.0f)
        return;

    base.position.x[index] += dx / d * speed * dt;
    base.position.y[index] += dy / d * speed * dt;
}

template<int NBase, int NTarget>
inline void moveEntityColCenterToward(
    Context &ctx,
    EntityBase<NBase> &base,
    uint32_t baseIndex,
    const AnchorPoint<NTarget> &target,
    uint32_t targetIndex,
    float speed)
{
    moveEntityColCenterToward(
        ctx,
        base,
        baseIndex,
        SDL_FPoint{target.x[targetIndex], target.y[targetIndex]},
        speed);
}
