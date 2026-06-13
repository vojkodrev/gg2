#pragma once
#include "../../structs/core/constants/CollisionConstants.h"
#include <cstdint>

inline uint32_t colIdIndex(uint32_t id)
{
    return id & COL_INDEX_MASK;
}
