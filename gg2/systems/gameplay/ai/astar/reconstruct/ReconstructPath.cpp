#include "ReconstructPath.h"
#include "../node/AStarDecode.h"
#include "../../../../../utils/hashmap/HashMapContains.h"
#include "../../../../../utils/hashmap/HashMapGet.h"

void reconstructPath(AStarContext& ctx, int current)
{
    ctx.pathLen = 0;

    while (hashMapContains(ctx.cameFrom, current, ctx.generation))
    {
        int x, y;
        astarDecode(ctx, current, x, y);

        if (ctx.pathLen < ASTAR_MAX_PATH)
            ctx.path[ctx.pathLen++] = { x, y };

        current = hashMapGet(ctx.cameFrom, current, ctx.generation, -1);
    }

    int x, y;
    astarDecode(ctx, current, x, y);
    if (ctx.pathLen < ASTAR_MAX_PATH)
        ctx.path[ctx.pathLen++] = { x, y };
}
