#pragma once
#include "SpatialHashConstants.h"

inline int spatialHashBucketOf(int cx, int cy)
{
    return ((cx * 1610612741) ^ (cy * 805306457)) & (SPATIAL_HASH_TABLE_SIZE - 1);
}
