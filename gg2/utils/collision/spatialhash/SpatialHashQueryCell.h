#pragma once
#include <cstdint>
#include <cstring>
#include "SpatialHash.h"
#include "SpatialHashBucketOf.h"

inline int spatialHashQueryCell(const SpatialHash &sh, int cx, int cy, uint32_t *out, int maxOut)
{
    int b = spatialHashBucketOf(sh, cx, cy);
    int n = sh.counts[b] < maxOut ? sh.counts[b] : maxOut;
    memcpy(out, sh.buckets[b], n * sizeof(uint32_t));
    return n;
}
