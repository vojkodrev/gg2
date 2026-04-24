#include "GetNeighbors.h"
#include "IsBlocked.h"
#include "../node/AStarEncode.h"
#include "../node/AStarDecode.h"

static const int DIR_X[8] = {  1, -1,  0,  0,  1,  1, -1, -1 };
static const int DIR_Y[8] = {  0,  0,  1, -1,  1, -1,  1, -1 };

// hash must be a collision state snapshot taken before pathfinding begins
int getNeighbors(const AStarContext& astar, const SpatialHash& hash, const Object& object,
                 int node, int speed, int* neighborsOut)
{
    int cx, cy;
    astarDecode(astar, node, cx, cy);

    int count = 0;
    for (int d = 0; d < 8; d++)
    {
        int nx = cx + DIR_X[d] * speed;
        int ny = cy + DIR_Y[d] * speed;

        if (isBlocked(hash, object, nx, ny))
            continue;

        neighborsOut[count++] = astarEncode(astar, nx, ny);
    }
    return count;
}
