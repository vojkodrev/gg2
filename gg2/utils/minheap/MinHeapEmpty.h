#pragma once
#include "MinHeap.h"

template<typename TValue, uint32_t TSize>
bool minHeapEmpty(const MinHeap<TValue, TSize>& h)
{
    return h.size == 0;
}
