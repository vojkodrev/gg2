#pragma once
#include <cstdint>
#include "../core/EntityBase.h"
#include "ObjectConstants.h"

struct Object
{
    uint32_t objectCount;
    int groupId[MAX_OBJECTS] = {};
    EntityBase<MAX_OBJECTS> base;
};
