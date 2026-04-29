#include "ReconstructPath.h"
#include "../../../../../utils/hashmap/HashMapTryGet.h"
#include "../node/AStarEncode.h"

int reconstructPath(AStarContext& ctx, int current, SDL_FPoint goalCenter, int* path)
{
    int pathLen = 0;

    int parent;
    while (hashMapTryGet(ctx.cameFrom, current, ctx.generation, parent))
    {
        if (pathLen < ASTAR_MAX_PATH)
            path[pathLen++] = current;

        current = parent;
    }

    for (int l = 0, r = pathLen - 1; l < r; l++, r--)
    {
        int tmp = path[l];
        path[l] = path[r];
        path[r] = tmp;
    }

    if (pathLen < ASTAR_MAX_PATH)
        path[pathLen++] = astarEncode(ctx, { (int)goalCenter.x, (int)goalCenter.y });

    return pathLen;
}
