#pragma once
#include "UpdateEntityAnchorCollisionFlipOnly.h"
#include "UpdateEntityFlipByParentFacing.h"
#include "../../../structs/core/EntityBase.h"
#include <cstdint>

template<int N>
inline void updateEntityAnchorCollisionFlipByParentFacing(
    const Facing<N> &parentFacing,
    EntityBase<N> &entityBase,
    uint32_t i)
{
    updateEntityFlipByParentFacing(parentFacing, entityBase.facing, i);
    updateEntityAnchorCollisionFlipOnly(entityBase, i);
}
