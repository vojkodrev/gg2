#pragma once
#include <cstdint>
#include "../entity/EntityBase.h"
#include "../groups/Group.h"
#include "ObjectConstants.h"

struct Object
{
    uint32_t objectCount;
    Group<MAX_OBJECTS> group;
    int zIndex[MAX_OBJECTS] = {};
    EntityBase<MAX_OBJECTS> base;
};
