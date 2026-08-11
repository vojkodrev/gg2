#pragma once
#include "../../structs/facing/Facing.h"
#include <cstdint>

template<int N>
inline bool setFacingTowardX(
    Facing<N> &facing,
    uint32_t i,
    float originX,
    float targetX)
{
    FacingDirection direction = facing.facing[i];
    if (targetX < originX)
        direction = FacingDirection::Left;
    else if (targetX > originX)
        direction = FacingDirection::Right;

    const bool changed = facing.facing[i] != direction;
    facing.dirty[i] = changed;
    facing.facing[i] = direction;
    return changed;
}
