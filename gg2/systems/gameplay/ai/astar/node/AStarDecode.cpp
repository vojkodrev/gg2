#include "AStarDecode.h"
#include "DecodeGridIndex.h"

SDL_Point astarDecode(const AStarContext& ctx, int node)
{
    SDL_Point grid = decodeGridIndex(node, ctx.searchW);
    return { grid.x + ctx.searchX, grid.y + ctx.searchY };
}
