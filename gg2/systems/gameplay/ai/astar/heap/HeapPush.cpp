#include "HeapPush.h"
#include "HeapSwap.h"

void heapPush(AStarHeap& h, int node, float fscore)
{
    int i = h.size++;
    h.nodes[i]   = node;
    h.fscores[i] = fscore;

    while (i > 0)
    {
        int parent = (i - 1) / 2;
        if (h.fscores[parent] <= h.fscores[i]) break;
        heapSwap(h, parent, i);
        i = parent;
    }
}
