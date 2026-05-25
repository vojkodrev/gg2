#pragma once
#include "UpdateEntityAnchorAndCollisionFlip.h"
#include "UpdateEntityFlipByParentFacing.h"
#include "../../../structs/core/EntityBase.h"
#include <cstdint>

template<int N>
inline void updateEntityAnchorAndCollisionFlipByParentFacing(
    const Facing<N> &parentFacing,
    EntityBase<N> &entityBase,
    uint32_t i)
{
    updateEntityFlipByParentFacing(parentFacing, entityBase.facing, i);
    updateEntityAnchorAndCollisionFlip(entityBase, i);
}
