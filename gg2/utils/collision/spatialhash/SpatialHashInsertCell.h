#pragma once
#include "SpatialHash.h"
#include "SpatialHashBucketOf.h"

inline void spatialHashInsertCell(SpatialHash &sh, int cx, int cy, uint16_t id)
{
    int b = spatialHashBucketOf(sh, cx, cy);
    if (sh.counts[b] < SpatialHash::MAX_PER_BUCKET)
        sh.buckets[b][sh.counts[b]++] = id;
}
