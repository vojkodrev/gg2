#include "ClosedContains.h"

static int closedSlot(int node)
{
    return (node * 2654435761u) >> (32 - 16);
}

bool closedContains(const AStarClosedSet& cs, int node, int generation)
{
    int slot = closedSlot(node);
    for (int i = 0; i < ASTAR_HASH_SIZE; i++)
    {
        int s = (slot + i) & (ASTAR_HASH_SIZE - 1);
        if (cs.gen[s] != generation) return false;
        if (cs.node[s] == node)      return true;
    }
    return false;
}
