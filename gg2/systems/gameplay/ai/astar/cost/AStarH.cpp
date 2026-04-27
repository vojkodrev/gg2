#include "AStarH.h"
#include "../node/AStarDecode.h"
#include <cmath>

float astarH(const AStarContext& ctx, int node, float tx, float ty)
{
    int nx, ny;
    astarDecode(ctx, node, nx, ny);
    float dx = tx - nx;
    float dy = ty - ny;
    return sqrtf(dx * dx + dy * dy);
}
