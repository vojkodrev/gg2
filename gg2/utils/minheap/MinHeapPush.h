#pragma once
#include "MinHeap.h"
#include "MinHeapSwap.h"

template<typename TValue, uint32_t TSize>
void minHeapPush(MinHeap<TValue, TSize>& h, int node, TValue value)
{
    uint32_t i = h.size++;
    h.nodes[i]  = node;
    h.values[i] = value;

    while (i > 0)
    {
        uint32_t parent = (i - 1) / 2;
        if (h.values[parent] <= h.values[i]) break;
        minHeapSwap(h, parent, i);
        i = parent;
    }
}
