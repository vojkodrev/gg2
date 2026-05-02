#include "AStarDecode.h"

SDL_Point astarDecode(const AStarContext& ctx, int node)
{
    return { node % ctx.searchW + ctx.searchX, node / ctx.searchW + ctx.searchY };
}
