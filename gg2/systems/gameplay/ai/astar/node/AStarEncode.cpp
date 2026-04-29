#include "AStarEncode.h"

int astarEncode(const AStarContext& ctx, SDL_Point p)
{
    return (p.y - ctx.searchY) * ctx.searchW + (p.x - ctx.searchX);
}
