#pragma once
#include "spatialhash/SpatialHash.h"
#include "CollisionResult.h"
#include "../../utils/collision/spatialhash/SpatialHashQueryCandidates.h"
#include <shared_mutex>

struct CollisionContext
{
    SpatialHash<1> spatialHash;
    SpatialHashQueryCandidates candidates;
    std::shared_mutex spatialHashMutex;
    CollisionResult collisions;
};
