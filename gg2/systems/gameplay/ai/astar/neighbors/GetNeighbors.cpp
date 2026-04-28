#include "GetNeighbors.h"
#include "../../../../../structs/core/Constants.h"
#include "IsBlocked.h"
#include "../node/AStarEncode.h"
#include "../node/AStarDecode.h"

static const int DIR_X[8] = {  1, -1,  0,  0,  1,  1, -1, -1 };
static const int DIR_Y[8] = {  0,  0,  1, -1,  1, -1,  1, -1 };

int getNeighbors(const AStarContext& astar, const Context& ctx,
                 int node, SDL_FRect startCol, int* neighborsOut)
{
    int cx, cy;
    astarDecode(astar, node, cx, cy);

    int minX = astar.searchX;
    int minY = astar.searchY;
    int maxX = astar.searchX + astar.searchW - 1;
    int maxY = astar.searchY + astar.searchH - 1;

    int count = 0;
    for (int d = 0; d < 8; d++)
    {
        int nx = cx + DIR_X[d] * NPC_MONSTER_PATH_STEP;
        int ny = cy + DIR_Y[d] * NPC_MONSTER_PATH_STEP;

        if (nx < minX || nx > maxX || ny < minY || ny > maxY)
            continue;

        if (isBlocked(astar, ctx, nx, ny, startCol))
            continue;

        neighborsOut[count++] = astarEncode(astar, nx, ny);
    }
    return count;
}
