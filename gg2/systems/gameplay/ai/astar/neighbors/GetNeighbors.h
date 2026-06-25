#pragma once
#include "../../../../../structs/gameplay/ai/AStarContext.h"
#include "../../../../../structs/core/Context.h"
#include "../node/AStarDecode.h"
#include "../node/AStarEncode.h"
#include "IsBlocked.h"
#include "NpcMonsterConstants.h"

template<uint32_t N>
int getNeighbors(
    const AStarContext<N>& astar,
    uint32_t astarIndex,
    const Context& ctx,
    int node,
    int npcIndex,
    int* neighborsOut)
{
    static const int DIR_X[8] = { 1, -1, 0, 0, 1, 1, -1, -1 };
    static const int DIR_Y[8] = { 0, 0, 1, -1, 1, -1, 1, -1 };

    SDL_Point c = astarDecode(astar, astarIndex, node);

    int minX = astar.searchX[astarIndex];
    int minY = astar.searchY[astarIndex];
    int maxX = astar.searchX[astarIndex] + astar.searchW[astarIndex] - 1;
    int maxY = astar.searchY[astarIndex] + astar.searchH[astarIndex] - 1;

    int count = 0;
    for (int d = 0; d < 8; d++)
    {
        SDL_Point nb = { c.x + DIR_X[d] * NPC_MONSTER_PATH_STEP,
                         c.y + DIR_Y[d] * NPC_MONSTER_PATH_STEP };

        if (nb.x < minX || nb.x > maxX || nb.y < minY || nb.y > maxY)
            continue;

        if (isBlocked(astar, astarIndex, ctx, nb, npcIndex))
            continue;

        neighborsOut[count++] = astarEncode(astar, astarIndex, nb);
    }

    return count;
}
