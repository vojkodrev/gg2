#include "AStarHeap.h"

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

int heapPop(AStarHeap& h)
{
    int result  = h.nodes[0];
    h.nodes[0]   = h.nodes[--h.size];
    h.fscores[0] = h.fscores[h.size];

    int i = 0;
    while (true)
    {
        int l = 2*i+1, r = 2*i+2, smallest = i;
        if (l < h.size && h.fscores[l] < h.fscores[smallest]) smallest = l;
        if (r < h.size && h.fscores[r] < h.fscores[smallest]) smallest = r;
        if (smallest == i) break;
        swap(h, i, smallest);
        i = smallest;
    }

    return result;
}

bool heapEmpty(const AStarHeap& h)
{
    return h.size == 0;
}
