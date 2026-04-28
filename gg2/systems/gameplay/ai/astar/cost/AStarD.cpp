#include "AStarD.h"

#include "../../../../../structs/core/Constants.h"

float astarD(const AStarContext& ctx, int fromNode, int toNode)
{
    int dx = (toNode % ctx.searchW) - (fromNode % ctx.searchW);
    int dy = (toNode / ctx.searchW) - (fromNode / ctx.searchW);
    return ((dx != 0 && dy != 0) ? 1.4142135f : 1.0f) * NPC_MONSTER_PATH_STEP;
}
