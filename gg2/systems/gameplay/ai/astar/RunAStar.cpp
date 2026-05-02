#include "RunAStar.h"
#include "../../../../structs/core/Context.h"
#include <shared_mutex>
#include "../../../../utils/collision/EntityColCenter.h"
#include "../../../../utils/minheap/MinHeapPush.h"
#include "../../../../utils/minheap/MinHeapPop.h"
#include "../../../../utils/minheap/MinHeapEmpty.h"
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
             SDL_FRect startCol, const SDL_FRect& destCol,
             int* pathOut)
{
    astar.status.store(AStarStatus::CALCULATING_PATH, std::memory_order_relaxed);

    Uint64 startTime = SDL_GetTicks();

    {
        std::shared_lock lock(ctx.collision.spatialHashMutex);
        astar.colHashSnapshot = ctx.collision.spatialHash;
    }

    SDL_FPoint startCenter = entityColCenter(startCol);

    astar.generation++;
    SDL_FPoint goalCenter = entityColCenter(destCol);

    int minX = (int)SDL_min(startCenter.x, goalCenter.x) - ASTAR_SEARCH_PAD;
    int minY = (int)SDL_min(startCenter.y, goalCenter.y) - ASTAR_SEARCH_PAD;
    int maxX = (int)SDL_max(startCenter.x, goalCenter.x) + ASTAR_SEARCH_PAD;
    int maxY = (int)SDL_max(startCenter.y, goalCenter.y) + ASTAR_SEARCH_PAD;

    astar.searchX = minX;
    astar.searchY = minY;
    astar.searchW = maxX - minX + 1;
    astar.searchH = maxY - minY + 1;

    int startNode = astarEncode(astar, { (int)startCenter.x, (int)startCenter.y });

    astar.fscoreHeap.size = 0;

    float h = astarH(astar, startNode, goalCenter);
    hashMapInsert(astar.gscores,  startNode, astar.generation, 0.0f);
    minHeapPush(astar.fscoreHeap, startNode, h);

    while (!minHeapEmpty(astar.fscoreHeap))
    {
        int current = minHeapPop(astar.fscoreHeap);

        if (hashMapContains(astar.closed, current, astar.generation))
            continue;

        hashMapInsert(astar.closed, current, astar.generation);

        if (isGoalReached(astar, destCol, current))
        {
            SDL_Log("AStar: %.2f ms", (float)(SDL_GetTicks() - startTime));
            int length = reconstructPath(astar, current, goalCenter, pathOut);
            astar.status.store(AStarStatus::FINISHED_CALCULATING, std::memory_order_relaxed);
            return length;
        }

        int neighbors[MAX_NEIGHBORS];
        int count = getNeighbors(astar, ctx, current, startCol, neighbors);

        float gCurrent;
        if (!hashMapTryGet(astar.gscores, current, astar.generation, gCurrent))
            continue;

        for (int i = 0; i < count; i++)
        {
            int nb = neighbors[i];
            if (hashMapContains(astar.closed, nb, astar.generation))
                continue;

            float tentativeG = gCurrent + astarD(astar, current, nb);

            float existingG;
            if (hashMapTryGet(astar.gscores, nb, astar.generation, existingG) &&
                tentativeG >= existingG)
                continue;

            hashMapInsert(astar.gscores,  nb, astar.generation, tentativeG);
            hashMapInsert(astar.cameFrom, nb, astar.generation, current);
            minHeapPush(astar.fscoreHeap, nb, tentativeG + astarH(astar, nb, goalCenter));
        }
    }

    astar.status.store(AStarStatus::PATH_NOT_FOUND, std::memory_order_relaxed);
    SDL_Log("AStar: path not found (%.2f ms)", (float)(SDL_GetTicks() - startTime));
    return -1;
}
