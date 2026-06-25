#pragma once
#include "../../../../../structs/gameplay/ai/AStarContext.h"
#include "../../../../../utils/grid/DecodeGridIndex.h"
#include "NpcMonsterConstants.h"

template<uint32_t N>
float astarD(const AStarContext<N>& ctx, uint32_t astarIndex, int fromNode, int toNode)
{
    const SDL_Point from = decodeGridIndex(fromNode, ctx.searchW[astarIndex]);
    const SDL_Point to = decodeGridIndex(toNode, ctx.searchW[astarIndex]);
    int dx = to.x - from.x;
    int dy = to.y - from.y;
    return ((dx != 0 && dy != 0) ? 1.4142135f : 1.0f) * NPC_MONSTER_PATH_STEP;
}
