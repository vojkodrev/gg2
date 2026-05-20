#pragma once
#include <cstdint>
#include "../core/Animation.h"
#include "../core/EntityPosition.h"
#include "CapacityConstants.h"

struct Object
{
    uint32_t objectCount;
    Animation<MAX_OBJECTS> animation;
    EntityPosition<MAX_OBJECTS> position;
    float scale[MAX_OBJECTS];
};
