#pragma once
#include "../../structs/core/constants/CollisionConstants.h"
#include "ColType.h"
#include <cstdint>

inline ColType colIdType(uint32_t id)
{
    return static_cast<ColType>(id >> COL_TYPE_SHIFT);
}
