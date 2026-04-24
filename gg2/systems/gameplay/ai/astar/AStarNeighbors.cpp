#include "AStarNeighbors.h"
#include "AStarNode.h"
#include "EntityAABB.h"
#include "ColId.h"
#include <SDL3/SDL.h>

static const int DIR_X[8] = {  1, -1,  0,  0,  1,  1, -1, -1 };
static const int DIR_Y[8] = {  0,  0,  1, -1,  1, -1,  1, -1 };

static bool isBlocked(const SpatialHash& hash, const Object& object, int wx, int wy)
{
    uint16_t candidates[SpatialHash::MAX_PER_BUCKET * 4];
    int n = hash.query((float)wx, (float)wy, 1.0f, 1.0f,
                       candidates, SpatialHash::MAX_PER_BUCKET * 4);

    SDL_FPoint p = { (float)wx, (float)wy };

    for (int i = 0; i < n; i++)
    {
        uint16_t id = candidates[i];
        if (!colIdIsObject(id))
            continue;

        SDL_FRect box = entityColAABB(object, colIdObjectIndex(id));

        if (SDL_PointInRectFloat(&p, &box))
            return true;
    }
    return false;
}

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
