#pragma once
#include <cstdint>
#include <cstring>
#include <SDL3/SDL.h>

// Flat spatial hash for broad-phase collision.
// Entities in the same grid cell are collision candidates.
// Uses open bucketing — different cells may share a bucket (false positives only,
// no false negatives), so callers must still do AABB tests.
struct SpatialHash
{
    static constexpr float CELL_SIZE = 64.0f;
    static constexpr int TABLE_SIZE = 4096; // must be power of 2
    static constexpr int MAX_PER_BUCKET = 16;

    uint16_t buckets[TABLE_SIZE][MAX_PER_BUCKET];
    uint8_t counts[TABLE_SIZE];

    void clear()
    {
        memset(counts, 0, sizeof(counts));
    }

    void insert(SDL_FRect rect, uint16_t id)
    {
        int minCx = (int)(rect.x / CELL_SIZE);
        int minCy = (int)(rect.y / CELL_SIZE);
        int maxCx = (int)((rect.x + rect.w) / CELL_SIZE);
        int maxCy = (int)((rect.y + rect.h) / CELL_SIZE);
        for (int cy = minCy; cy <= maxCy; cy++)
            for (int cx = minCx; cx <= maxCx; cx++)
                insertCell(cx, cy, id);
    }

    int query(SDL_FRect rect, uint16_t *out, int maxOut) const
    {
        int minCx = (int)(rect.x / CELL_SIZE);
        int minCy = (int)(rect.y / CELL_SIZE);
        int maxCx = (int)((rect.x + rect.w) / CELL_SIZE);
        int maxCy = (int)((rect.y + rect.h) / CELL_SIZE);
        int total = 0;
        for (int cy = minCy; cy <= maxCy && total < maxOut; cy++)
            for (int cx = minCx; cx <= maxCx && total < maxOut; cx++)
                total += queryCell(cx, cy, out + total, maxOut - total);
        return total;
    }

private:
    int bucketOf(int cx, int cy) const
    {
        return ((cx * 1610612741) ^ (cy * 805306457)) & (TABLE_SIZE - 1);
    }

    void insertCell(int cx, int cy, uint16_t id)
    {
        int b = bucketOf(cx, cy);
        if (counts[b] < MAX_PER_BUCKET)
            buckets[b][counts[b]++] = id;
    }

    int queryCell(int cx, int cy, uint16_t *out, int maxOut) const
    {
        int b = bucketOf(cx, cy);
        int n = counts[b] < maxOut ? counts[b] : maxOut;
        memcpy(out, buckets[b], n * sizeof(uint16_t));
        return n;
    }
};
