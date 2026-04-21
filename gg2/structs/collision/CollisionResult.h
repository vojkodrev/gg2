#pragma once
#include "CollisionPair.h"
#include "constants.h"

// Entity ID encoding: 0 = player, 1..N = NPC index (id - 1)
struct CollisionResult
{
    CollisionPair pairs[MAX_COLLISION_PAIRS];
    uint32_t count;
};
