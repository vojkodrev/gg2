#pragma once
#include "UpdateEntityAnchorCollisionOffsetFlip.h"
#include "UpdateEntityFlip.h"
#include "../../../structs/core/EntityBase.h"
#include <cstdint>

template<int N>
inline void updateEntityAnchorCollisionFlip(EntityBase<N> &entityBase, uint32_t i)
{
    updateEntityFlip(entityBase.facing, i);
    updateEntityAnchorCollisionOffsetFlip(entityBase, i);
}
