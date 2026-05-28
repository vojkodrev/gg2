#pragma once
#include <cstdint>
#include "../core/EntityBase.h"
#include "CapacityConstants.h"

struct Object
{
    uint32_t objectCount;
    EntityBase<MAX_OBJECTS> base;
};
