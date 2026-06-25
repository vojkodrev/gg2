#include "AStarDecode.h"
#include "DecodeGridIndex.h"

template<uint32_t N>
SDL_Point astarDecode(const AStarContext<N>& ctx, uint32_t astarIndex, int node)
{
    SDL_Point grid = decodeGridIndex(node, ctx.searchW[astarIndex]);
    return { grid.x + ctx.searchX[astarIndex], grid.y + ctx.searchY[astarIndex] };
}
