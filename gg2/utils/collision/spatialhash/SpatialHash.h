#pragma once
#include <cstdint>
#include "SpatialHashConstants.h"

// Flat spatial hash for broad-phase collision.
// Entities in the same grid cell are collision candidates.
// Uses open bucketing — different cells may share a bucket (false positives only,
// no false negatives), so callers must still do AABB tests.
template<uint32_t N>
struct SpatialHash
{
    uint32_t buckets[N][SPATIAL_HASH_TABLE_SIZE][SPATIAL_HASH_MAX_PER_BUCKET];
    uint8_t counts[N][SPATIAL_HASH_TABLE_SIZE];
};
