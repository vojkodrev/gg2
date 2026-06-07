#pragma once
#include "../../../structs/core/Facing.h"
#include <cstdint>

template<int N>
inline void syncFlipFromFacing(Facing<N> &facing, uint32_t i)
{
    facing.flipX[i] = facing.facing[i] != facing.initialFacing[i];
}
