#pragma once
#include <cstdint>
#include "CollisionConstants.h"

struct CollisionPair
{
    uint16_t a[MAX_COLLISION_PAIRS];
    uint16_t b[MAX_COLLISION_PAIRS];
};
