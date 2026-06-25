#pragma once
#include "MinHeap.h"
#include "MinHeapSwap.h"

template<uint32_t N, typename TValue, uint32_t TSize>
void minHeapPush(MinHeap<N, TSize, TValue>& h, uint32_t index, int node, TValue value)
{
    uint32_t i = h.size[index]++;
    h.nodes[index][i]  = node;
    h.values[index][i] = value;

    while (i > 0)
    {
        uint32_t parent = (i - 1) / 2;
        if (h.values[index][parent] <= h.values[index][i]) break;
        minHeapSwap(h, index, parent, i);
        i = parent;
    }
}
