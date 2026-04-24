#include "ClosedInsert.h"
#include "ClosedSlot.h"

void closedInsert(AStarClosedSet& cs, int node, int generation)
{
    int slot = closedSlot(node);
    for (int i = 0; i < ASTAR_HASH_SIZE; i++)
    {
        int s = (slot + i) & (ASTAR_HASH_SIZE - 1);
        if (cs.gen[s] != generation || cs.node[s] == node)
        {
            cs.node[s] = node;
            cs.gen[s]  = generation;
            return;
        }
    }
}
