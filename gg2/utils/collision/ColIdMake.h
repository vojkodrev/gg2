#pragma once
#include "../../structs/core/constants/CollisionConstants.h"
#include "ColType.h"
#include <cstdint>

inline uint32_t colIdMake(ColType type, uint32_t index)
{
    return (static_cast<uint32_t>(type) << COL_TYPE_SHIFT) | (index & COL_INDEX_MASK);
}
