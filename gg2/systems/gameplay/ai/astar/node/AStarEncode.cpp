#include "AStarEncode.h"
#include "EncodeGridIndex.h"

template<uint32_t N>
int astarEncode(const AStarContext<N>& ctx, uint32_t astarIndex, SDL_Point p)
{
    return encodeGridIndex(
        { p.x - ctx.searchX[astarIndex], p.y - ctx.searchY[astarIndex] },
        ctx.searchW[astarIndex]);
}
