#pragma once
#include "SpatialHash.h"
#include "CollisionResult.h"

struct CollisionContext
{
    SpatialHash spatialHash;
    CollisionResult collisions;
};
