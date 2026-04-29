#include "AStarDecode.h"

void astarDecode(const AStarContext& ctx, int node, SDL_Point& p)
{
    p.x = node % ctx.searchW + ctx.searchX;
    p.y = node / ctx.searchW + ctx.searchY;
}
