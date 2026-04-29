#pragma once
#include "SpatialHash.h"

inline int spatialHashBucketOf(const SpatialHash &sh, int cx, int cy)
{
    return ((cx * 1610612741) ^ (cy * 805306457)) & (SpatialHash::TABLE_SIZE - 1);
}
