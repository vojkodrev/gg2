#include "AStarDecode.h"

void astarDecode(const AStarContext& ctx, int node, int& x, int& y)
{
    x = node % ctx.searchW + ctx.searchX;
    y = node / ctx.searchW + ctx.searchY;
}
