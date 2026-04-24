#include "AStarH.h"
#include <cmath>

float astarH(const AStarContext& ctx, int node, float tx, float ty)
{
    int nx = node % ASTAR_SEARCH_D + ctx.offsetX;
    int ny = node / ASTAR_SEARCH_D + ctx.offsetY;
    float dx = tx - nx;
    float dy = ty - ny;
    return sqrtf(dx * dx + dy * dy);
}
