#pragma once
#include <cstdint>

template<typename TValue, uint32_t TSize>
struct MinHeap
{
    int      nodes[TSize];
    TValue   values[TSize];
    uint32_t size;
};
