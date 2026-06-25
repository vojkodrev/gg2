#pragma once
#include "MinHeap.h"
#include "MinHeapSwap.h"

template<uint32_t N, typename TValue, uint32_t TSize>
int minHeapPop(MinHeap<N, TSize, TValue>& h, uint32_t index)
{
    int result  = h.nodes[index][0];
    h.nodes[index][0]  = h.nodes[index][--h.size[index]];
    h.values[index][0] = h.values[index][h.size[index]];

    uint32_t i = 0;
    while (true)
    {
        uint32_t l = 2*i+1, r = 2*i+2, smallest = i;
        if (l < h.size[index] && h.values[index][l] < h.values[index][smallest]) smallest = l;
        if (r < h.size[index] && h.values[index][r] < h.values[index][smallest]) smallest = r;
        if (smallest == i) break;
        minHeapSwap(h, index, i, smallest);
        i = smallest;
    }

    return result;
}
