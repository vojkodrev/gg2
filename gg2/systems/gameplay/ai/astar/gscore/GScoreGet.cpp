#include "GScoreGet.h"
#include "GScoreSlot.h"
#include <cfloat>

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
