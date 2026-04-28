#include "AStarEncode.h"

int astarEncode(const AStarContext& ctx, int x, int y)
{
    return (y - ctx.searchY) * ctx.searchW + (x - ctx.searchX);
}
