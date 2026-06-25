#pragma once
#include <cstdint>
#include <cstring>
#include "SpatialHash.h"
#include "SpatialHashBucketOf.h"

template<uint32_t N>
inline int spatialHashQueryCell(
    const SpatialHash<N> &sh,
    uint32_t index,
    int cx,
    int cy,
    uint32_t *out,
    int maxOut)
{
    int b = spatialHashBucketOf(cx, cy);
    int n = sh.counts[index][b] < maxOut ? sh.counts[index][b] : maxOut;
    memcpy(out, sh.buckets[index][b], n * sizeof(uint32_t));
    return n;
}
