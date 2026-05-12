#include "AStarEncode.h"
#include "EncodeGridIndex.h"

int astarEncode(const AStarContext& ctx, SDL_Point p)
{
    return encodeGridIndex({ p.x - ctx.searchX, p.y - ctx.searchY }, ctx.searchW);
}
