#pragma once
#include "UpdateEntityFlipByParentFacing.h"
#include "../../../structs/core/Facing.h"
#include <cstdint>

template<int N>
inline void updateEntityFacingDirtyByParentFacing(
    const Facing<N> &parentFacing,
    Facing<N> &entityFacing,
    uint32_t i)
{
    entityFacing.dirty[i] = false;
    bool entityFlipX = entityFacing.flipX[i];
    updateEntityFlipByParentFacing(parentFacing, entityFacing, i);
    entityFacing.dirty[i] = entityFacing.flipX[i] != entityFlipX;
}
