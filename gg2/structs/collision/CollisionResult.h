#pragma once
#include "CollisionPair.h"

// Collision ids are packed uint32_t values with type bits in the high byte
// and entity index bits in the low 24 bits.
struct CollisionResult
{
    CollisionPair pair;
    uint32_t count;
};
