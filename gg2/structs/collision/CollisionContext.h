#pragma once
#include "spatialhash/SpatialHash.h"
#include "CollisionResult.h"

struct CollisionContext
{
    SpatialHash spatialHash;
    CollisionResult collisions;
};
