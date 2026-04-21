#pragma once
#include "constants.h"
#include "CollisionPair.h"

// Entity ID encoding: 0 = player, 1..N = NPC index (id - 1)
struct CollisionResult
{
    CollisionPair pair;
    uint32_t count;
};
