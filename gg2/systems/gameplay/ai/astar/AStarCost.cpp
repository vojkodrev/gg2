#include "AStarCost.h"
#include <cmath>

float astarH(const AStarContext& ctx, int node, float tx, float ty)
{
    int nx = node % ASTAR_SEARCH_D + ctx.offsetX;
    int ny = node / ASTAR_SEARCH_D + ctx.offsetY;
    float dx = tx - nx;
    float dy = ty - ny;
    return sqrtf(dx * dx + dy * dy);
}

float astarD(int fromNode, int toNode)
{
    int dx = (toNode % ASTAR_SEARCH_D) - (fromNode % ASTAR_SEARCH_D);
    int dy = (toNode / ASTAR_SEARCH_D) - (fromNode / ASTAR_SEARCH_D);
    return (dx != 0 && dy != 0) ? 1.4142135f : 1.0f;
}
