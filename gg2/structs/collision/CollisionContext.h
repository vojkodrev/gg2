#pragma once
#include "spatialhash/SpatialHash.h"
#include "spatialhash/SpatialHashConstants.h"
#include "CollisionResult.h"
#include <shared_mutex>

struct CollisionContext
{
    SpatialHash<1> spatialHash;
    uint32_t candidates[SPATIAL_HASH_MAX_PER_BUCKET * 4];
    std::shared_mutex spatialHashMutex;
    CollisionResult collisions;
    CollisionResult effectCollisions;
};
