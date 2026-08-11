#pragma once
#include "../../../../../structs/astar/AStarContext.h"
#include "../../../../../utils/hashmap/HashMapTryGet.h"
#include "../node/AStarEncode.h"
#include <SDL3/SDL.h>

template<uint32_t N>
int reconstructPath(
    AStarContext<N>& ctx,
    uint32_t astarIndex,
    int current,
    SDL_FPoint goalCenter,
    int* path)
{
    int pathLen = 0;

    int parent;
    while (hashMapTryGet(ctx.cameFrom, astarIndex, current, ctx.generation[astarIndex], parent))
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
        path[pathLen++] = astarEncode(ctx, astarIndex, { (int)goalCenter.x, (int)goalCenter.y });

    return pathLen;
}
