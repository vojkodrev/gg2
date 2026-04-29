#include "AStarH.h"
#include "../node/AStarDecode.h"
#include <cmath>

float astarH(const AStarContext& ctx, int node, SDL_FPoint target)
{
    SDL_Point p;
    astarDecode(ctx, node, p);
    float dx = target.x - p.x;
    float dy = target.y - p.y;
    return sqrtf(dx * dx + dy * dy);
}
