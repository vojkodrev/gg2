#pragma once
#include "SyncFlipFromParentFacing.h"
#include "../../../structs/core/Facing.h"
#include <cstdint>

template<int N>
inline void syncFlipFromParentFacingAndMarkDirty(
    const Facing<N> &parentFacing,
    Facing<N> &entityFacing,
    uint32_t i)
{
    bool entityFlipX = entityFacing.flipX[i];
    syncFlipFromParentFacing(parentFacing, entityFacing, i);
    entityFacing.dirty[i] = entityFacing.flipX[i] != entityFlipX;
}
