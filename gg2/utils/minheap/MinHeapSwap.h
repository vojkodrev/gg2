#pragma once
#include "MinHeap.h"

template<uint32_t N, typename TValue, uint32_t TSize>
void minHeapSwap(MinHeap<N, TSize, TValue>& h, uint32_t index, uint32_t a, uint32_t b)
{
    int    tn = h.nodes[index][a];  h.nodes[index][a]  = h.nodes[index][b];  h.nodes[index][b]  = tn;
    TValue tv = h.values[index][a]; h.values[index][a] = h.values[index][b]; h.values[index][b] = tv;
}
