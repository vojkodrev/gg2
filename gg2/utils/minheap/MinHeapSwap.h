#pragma once
#include "MinHeap.h"

template<typename TValue, uint32_t TSize>
void minHeapSwap(MinHeap<TValue, TSize>& h, uint32_t a, uint32_t b)
{
    int    tn = h.nodes[a];  h.nodes[a]  = h.nodes[b];  h.nodes[b]  = tn;
    TValue tv = h.values[a]; h.values[a] = h.values[b]; h.values[b] = tv;
}
