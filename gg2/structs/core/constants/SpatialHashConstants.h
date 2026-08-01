#pragma once

constexpr float SPATIAL_HASH_CELL_SIZE = 64.0f;
constexpr int SPATIAL_HASH_TABLE_SIZE = 4096; // must be power of 2
constexpr int SPATIAL_HASH_MAX_PER_BUCKET = 16;
constexpr int SPATIAL_HASH_MAX_QUERY_RESULTS =
    SPATIAL_HASH_MAX_PER_BUCKET * 4;
