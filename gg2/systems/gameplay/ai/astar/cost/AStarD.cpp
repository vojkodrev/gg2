#include "AStarD.h"

float astarD(const AStarContext& ctx, int fromNode, int toNode, int speed)
{
    int dx = (toNode % ctx.searchW) - (fromNode % ctx.searchW);
    int dy = (toNode / ctx.searchW) - (fromNode / ctx.searchW);
    return ((dx != 0 && dy != 0) ? 1.4142135f : 1.0f) * speed;
}
