#include "HeapPush.h"

static void swap(AStarHeap& h, int a, int b)
{
    int   tn = h.nodes[a];   h.nodes[a]   = h.nodes[b];   h.nodes[b]   = tn;
    float tf = h.fscores[a]; h.fscores[a] = h.fscores[b]; h.fscores[b] = tf;
}

void heapPush(AStarHeap& h, int node, float fscore)
{
    int i = h.size++;
    h.nodes[i]   = node;
    h.fscores[i] = fscore;

    while (i > 0)
    {
        int parent = (i - 1) / 2;
        if (h.fscores[parent] <= h.fscores[i]) break;
        swap(h, parent, i);
        i = parent;
    }
}
