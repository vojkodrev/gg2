#pragma once
#include "../../../structs/core/Facing.h"
#include <cstdint>

template<int N>
inline void updateEntityFlipByParentFacing(
    const Facing<N> &parentFacing,
    Facing<N> &entityFacing,
    uint32_t i)
{
    bool parentNeedsFlip = parentFacing.facing[i] != entityFacing.initialFacing[i];
    bool entityFacingChanged = entityFacing.facing[i] != entityFacing.initialFacing[i];
    entityFacing.flipX[i] = parentNeedsFlip != entityFacingChanged;
}
