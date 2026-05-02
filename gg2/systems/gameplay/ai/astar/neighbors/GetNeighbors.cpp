#include "GetNeighbors.h"
#include "../../../../../structs/core/Constants.h"
#include "IsBlocked.h"
#include "../node/AStarEncode.h"
#include "../node/AStarDecode.h"

static const int DIR_X[8] = {  1, -1,  0,  0,  1,  1, -1, -1 };
static const int DIR_Y[8] = {  0,  0,  1, -1,  1, -1,  1, -1 };

int getNeighbors(const AStarContext& astar, const Context& ctx,
                 int node, int npcIndex, int* neighborsOut)
{
    SDL_Point c = astarDecode(astar, node);

    int minX = astar.searchX;
    int minY = astar.searchY;
    int maxX = astar.searchX + astar.searchW - 1;
    int maxY = astar.searchY + astar.searchH - 1;

    int count = 0;
    for (int d = 0; d < 8; d++)
    {
        SDL_Point nb = { c.x + DIR_X[d] * NPC_MONSTER_PATH_STEP,
                         c.y + DIR_Y[d] * NPC_MONSTER_PATH_STEP };

        if (nb.x < minX || nb.x > maxX || nb.y < minY || nb.y > maxY)
            continue;

        if (isBlocked(astar, ctx, nb, npcIndex))
            continue;

        neighborsOut[count++] = astarEncode(astar, nb);
    }
    return count;
}
