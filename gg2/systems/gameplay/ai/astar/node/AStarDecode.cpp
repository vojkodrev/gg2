#include "AStarDecode.h"

void astarDecode(const AStarContext& ctx, int node, int& x, int& y)
{
    x = node % ASTAR_SEARCH_D + ctx.offsetX;
    y = node / ASTAR_SEARCH_D + ctx.offsetY;
}
