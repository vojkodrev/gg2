#pragma once
#include "MirrorEntityAnchorsAndCollisionOffsets.h"
#include "SyncFlipFromFacing.h"
#include "../../../structs/core/EntityBase.h"
#include <cstdint>

template<int N>
inline void syncEntityFlipAndMirrorOffsets(EntityBase<N> &entityBase, uint32_t i)
{
    syncFlipFromFacing(entityBase.facing, i);
    mirrorEntityAnchorsAndCollisionOffsets(entityBase, i);
}
