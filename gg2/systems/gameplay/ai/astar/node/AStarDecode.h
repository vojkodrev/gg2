#pragma once
#include "../../../../../structs/gameplay/ai/AStarContext.h"
#include "../../../../../utils/grid/DecodeGridIndex.h"
#include <SDL3/SDL.h>

template<uint32_t N>
SDL_Point astarDecode(const AStarContext<N>& ctx, uint32_t astarIndex, int node)
{
    SDL_Point grid = decodeGridIndex(node, ctx.searchW[astarIndex]);
    return { grid.x + ctx.searchX[astarIndex], grid.y + ctx.searchY[astarIndex] };
}
