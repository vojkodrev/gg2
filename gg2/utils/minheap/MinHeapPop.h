#pragma once
#include "MinHeap.h"
#include "MinHeapSwap.h"

template<typename TValue, uint32_t TSize>
int minHeapPop(MinHeap<TValue, TSize>& h)
{
    int result  = h.nodes[0];
    h.nodes[0]  = h.nodes[--h.size];
    h.values[0] = h.values[h.size];

    uint32_t i = 0;
    while (true)
    {
        uint32_t l = 2*i+1, r = 2*i+2, smallest = i;
        if (l < h.size && h.values[l] < h.values[smallest]) smallest = l;
        if (r < h.size && h.values[r] < h.values[smallest]) smallest = r;
        if (smallest == i) break;
        minHeapSwap(h, i, smallest);
        i = smallest;
    }

    return result;
}
