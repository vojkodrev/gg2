#pragma once
#include <cstdint>
#include "../core/EntityBase.h"
#include "ObjectConstants.h"

struct Object
{
    uint32_t objectCount;
    EntityBase<MAX_OBJECTS> base;
};
