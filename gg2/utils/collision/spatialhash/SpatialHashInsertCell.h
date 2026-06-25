#pragma once
#include "SpatialHash.h"
#include "SpatialHashConstants.h"
#include "SpatialHashBucketOf.h"

template<uint32_t N>
inline void spatialHashInsertCell(SpatialHash<N> &sh, uint32_t index, int cx, int cy, uint32_t id)
{
    int b = spatialHashBucketOf(cx, cy);
    if (sh.counts[index][b] < SPATIAL_HASH_MAX_PER_BUCKET)
        sh.buckets[index][b][sh.counts[index][b]++] = id;
}
