#include "AStarEncode.h"

int astarEncode(const AStarContext& ctx, int x, int y)
{
    return (y - ctx.offsetY) * ASTAR_SEARCH_D + (x - ctx.offsetX);
}
