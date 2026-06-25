#pragma once
#include "MinHeap.h"

template<uint32_t N, typename TValue, uint32_t TSize>
bool minHeapEmpty(const MinHeap<N, TSize, TValue>& h, uint32_t index)
{
    return h.size[index] == 0;
}
