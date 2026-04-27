#include "RunAStar.h"
#include "../../../../structs/core/Context.h"
#include "../../../../utils/collision/EntityAABB.h"
#include "heap/HeapPush.h"
#include "heap/HeapPop.h"
#include "heap/HeapEmpty.h"
#include "cost/AStarH.h"
#include "cost/AStarD.h"
#include "neighbors/GetNeighbors.h"
#include "goal/IsGoalReached.h"
#include "reconstruct/ReconstructPath.h"
#include "node/AStarEncode.h"
#include "../../../../utils/hashmap/HashMapInsert.h"
#include "../../../../utils/hashmap/HashMapInsertVoid.h"
#include "../../../../utils/hashmap/HashMapContains.h"
#include "../../../../utils/hashmap/HashMapTryGet.h"

static const int MAX_NEIGHBORS = 8;

int runAStar(AStarContext& astar, Context& ctx,
             SDL_FPoint start, const SDL_FRect& destCol, int speed,
             int* pathOut)
{
    astar.status = AStarStatus::CALCULATING_PATH;

    Uint64 startTime = SDL_GetTicks();

    SpatialHash colHashSnapshot = ctx.collision.spatialHash;

    astar.generation++;
    astar.offsetX = (int)start.x - ASTAR_SEARCH_R;
    astar.offsetY = (int)start.y - ASTAR_SEARCH_R;

    int startNode = astarEncode(astar, (int)start.x, (int)start.y);

    SDL_FPoint goalCenter = entityColCenter(destCol);
    float goalX = goalCenter.x;
    float goalY = goalCenter.y;

    astar.fscoreHeap.size = 0;

    float h = astarH(astar, startNode, goalX, goalY);
    hashMapInsert(astar.gscores,  startNode, astar.generation, 0.0f);
    heapPush(astar.fscoreHeap, startNode, h);

    while (!heapEmpty(astar.fscoreHeap))
    {
        int current = heapPop(astar.fscoreHeap);

        if (hashMapContains(astar.closed, current, astar.generation))
            continue;
        hashMapInsert(astar.closed, current, astar.generation);

        if (isGoalReached(astar, destCol, current))
        {
            astar.status = AStarStatus::FINISHED_CALCULATING;
            SDL_Log("AStar: %.2f ms", (float)(SDL_GetTicks() - startTime));
            return reconstructPath(astar, current, pathOut);
        }

        int neighbors[MAX_NEIGHBORS];
        int count = getNeighbors(astar, colHashSnapshot, ctx, current, speed, neighbors);

        float gCurrent;
        if (!hashMapTryGet(astar.gscores, current, astar.generation, gCurrent))
            continue;

        for (int i = 0; i < count; i++)
        {
            int nb = neighbors[i];
            if (hashMapContains(astar.closed, nb, astar.generation))
                continue;

            float tentativeG = gCurrent + astarD(current, nb, speed);

            float existingG;
            if (hashMapTryGet(astar.gscores, nb, astar.generation, existingG) &&
                tentativeG >= existingG)
                continue;

            hashMapInsert(astar.gscores,  nb, astar.generation, tentativeG);
            hashMapInsert(astar.cameFrom, nb, astar.generation, current);
            heapPush(astar.fscoreHeap, nb, tentativeG + astarH(astar, nb, goalX, goalY));
        }
    }

    astar.status = AStarStatus::PATH_NOT_FOUND;
    SDL_Log("AStar: path not found (%.2f ms)", (float)(SDL_GetTicks() - startTime));
    return -1;
}
