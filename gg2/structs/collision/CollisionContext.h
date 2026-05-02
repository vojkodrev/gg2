#pragma once
#include "spatialhash/SpatialHash.h"
#include "CollisionResult.h"
#include <shared_mutex>

struct CollisionContext
{
    SpatialHash spatialHash;
    std::shared_mutex spatialHashMutex;
    CollisionResult collisions;
};
