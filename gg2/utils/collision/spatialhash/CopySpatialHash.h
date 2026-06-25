#pragma once
#include "SpatialHash.h"
#include <cstring>

template<uint32_t TToN, uint32_t TFromN>
inline void copySpatialHash(
    SpatialHash<TToN> &to,
    uint32_t toIndex,
    const SpatialHash<TFromN> &from,
    uint32_t fromIndex)
{
    memcpy(
        to.buckets[toIndex],
        from.buckets[fromIndex],
        sizeof(from.buckets[fromIndex]));
    memcpy(
        to.counts[toIndex],
        from.counts[fromIndex],
        sizeof(from.counts[fromIndex]));
}
