#include "AStarGScoreMap.h"
#include <cfloat>

static int gscoreSlot(int node)
{
    return (node * 2654435761u) >> (32 - 16);
}

void gscoreSet(AStarGScoreMap& gm, int node, int generation, float g)
{
    int slot = gscoreSlot(node);
    for (int i = 0; i < ASTAR_HASH_SIZE; i++)
    {
        int s = (slot + i) & (ASTAR_HASH_SIZE - 1);
        if (gm.gen[s] != generation || gm.node[s] == node)
        {
            gm.node[s]   = node;
            gm.gen[s]    = generation;
            gm.gscore[s] = g;
            return;
        }
    }
}

float gscoreGet(const AStarGScoreMap& gm, int node, int generation)
{
    int slot = gscoreSlot(node);
    for (int i = 0; i < ASTAR_HASH_SIZE; i++)
    {
        int s = (slot + i) & (ASTAR_HASH_SIZE - 1);
        if (gm.gen[s] != generation) return FLT_MAX;
        if (gm.node[s] == node)      return gm.gscore[s];
    }
    return FLT_MAX;
}
