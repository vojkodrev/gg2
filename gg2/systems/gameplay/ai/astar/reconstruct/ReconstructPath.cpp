#include "ReconstructPath.h"
#include "../../../../../utils/hashmap/HashMapTryGet.h"

void reconstructPath(AStarContext& ctx, int current)
{
    ctx.pathLen = 0;

    int parent;
    while (hashMapTryGet(ctx.cameFrom, current, ctx.generation, parent))
    {
        if (ctx.pathLen < ASTAR_MAX_PATH)
            ctx.path[ctx.pathLen++] = current;

        current = parent;
    }

    if (ctx.pathLen < ASTAR_MAX_PATH)
        ctx.path[ctx.pathLen++] = current;
}
