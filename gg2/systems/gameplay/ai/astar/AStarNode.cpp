#include "AStarNode.h"

int astarEncode(const AStarContext& ctx, int x, int y)
{
    return (y - ctx.offsetY) * ASTAR_SEARCH_D + (x - ctx.offsetX);
}

void astarDecode(const AStarContext& ctx, int node, int& x, int& y)
{
    x = node % ASTAR_SEARCH_D + ctx.offsetX;
    y = node / ASTAR_SEARCH_D + ctx.offsetY;
}
