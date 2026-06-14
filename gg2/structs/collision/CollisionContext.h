#pragma once
#include "spatialhash/SpatialHash.h"
#include "CollisionResult.h"
#include <shared_mutex>

struct CollisionContext
{
    SpatialHash spatialHash;
    uint32_t candidates[SpatialHash::MAX_PER_BUCKET * 4];
    std::shared_mutex spatialHashMutex;
    CollisionResult collisions;
};
