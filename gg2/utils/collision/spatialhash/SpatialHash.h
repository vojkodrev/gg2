#pragma once
#include <cstdint>

// Flat spatial hash for broad-phase collision.
// Entities in the same grid cell are collision candidates.
// Uses open bucketing — different cells may share a bucket (false positives only,
// no false negatives), so callers must still do AABB tests.
struct SpatialHash
{
    static constexpr float CELL_SIZE = 64.0f;
    static constexpr int TABLE_SIZE = 4096; // must be power of 2
    static constexpr int MAX_PER_BUCKET = 16;

    uint32_t buckets[TABLE_SIZE][MAX_PER_BUCKET];
    uint8_t counts[TABLE_SIZE];
};
