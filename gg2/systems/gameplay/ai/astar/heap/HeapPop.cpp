#include "HeapPop.h"
#include "HeapSwap.h"

int heapPop(AStarHeap& h)
{
    int result   = h.nodes[0];
    h.nodes[0]   = h.nodes[--h.size];
    h.fscores[0] = h.fscores[h.size];

    int i = 0;
    while (true)
    {
        int l = 2*i+1, r = 2*i+2, smallest = i;
        if (l < h.size && h.fscores[l] < h.fscores[smallest]) smallest = l;
        if (r < h.size && h.fscores[r] < h.fscores[smallest]) smallest = r;
        if (smallest == i) break;
        heapSwap(h, i, smallest);
        i = smallest;
    }

    return result;
}
