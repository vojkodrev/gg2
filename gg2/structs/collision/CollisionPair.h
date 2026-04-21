#pragma once
#include <cstdint>

struct CollisionPair
{
    uint16_t a[MAX_COLLISION_PAIRS];
    uint16_t b[MAX_COLLISION_PAIRS];
};
