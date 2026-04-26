#include "ReconstructPath.h"
#include "../../../../../utils/hashmap/HashMapTryGet.h"

int reconstructPath(AStarContext& ctx, int current, int* path)
{
    int pathLen = 0;

    int parent;
    while (hashMapTryGet(ctx.cameFrom, current, ctx.generation, parent))
    {
        if (pathLen < ASTAR_MAX_PATH)
            path[pathLen++] = current;

        current = parent;
    }

    if (pathLen < ASTAR_MAX_PATH)
        path[pathLen++] = current;

    return pathLen;
}
