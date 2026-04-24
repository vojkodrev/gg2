#include "HeapSwap.h"

void heapSwap(AStarHeap& h, int a, int b)
{
    int   tn = h.nodes[a];   h.nodes[a]   = h.nodes[b];   h.nodes[b]   = tn;
    float tf = h.fscores[a]; h.fscores[a] = h.fscores[b]; h.fscores[b] = tf;
}
