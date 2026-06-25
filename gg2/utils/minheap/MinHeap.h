#pragma once
#include <cstdint>

template<uint32_t N, uint32_t TSize, typename TValue>
struct MinHeap
{
    int      nodes[N][TSize];
    TValue   values[N][TSize];
    uint32_t size[N];
};
