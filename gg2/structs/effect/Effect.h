#pragma once
#include <cstdint>
#include "../core/EntityBase.h"
#include "CapacityConstants.h"

struct Effect
{
    uint32_t effectCount;
    EntityBase<MAX_EFFECTS> base;
};
