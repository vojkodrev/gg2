#pragma once
#include <cstdint>
#include "CollisionConstants.h"

struct CollisionPair
{
    uint32_t a[MAX_COLLISION_PAIRS];
    uint32_t b[MAX_COLLISION_PAIRS];
};
