#pragma once
#include "../../../../structs/ai/AStarContext.h"
#include "../../../../structs/core/Context.h"
#include "../../../../structs/core/constants/IndexConstants.h"
#include "../../../../utils/collision/EntityColCenter.h"
#include "../../../../utils/collision/spatialhash/CopySpatialHash.h"
#include "../../../../utils/hashmap/HashMapContains.h"
#include "../../../../utils/hashmap/HashMapInsert.h"
#include "../../../../utils/hashmap/HashMapInsertVoid.h"
#include "../../../../utils/hashmap/HashMapTryGet.h"
#include "../../../../utils/minheap/MinHeapEmpty.h"
#include "../../../../utils/minheap/MinHeapPop.h"
#include "../../../../utils/minheap/MinHeapPush.h"
#include "../../../../utils/Defer.h"
#include "../../../../utils/math/CalcEma.h"
#include "cost/AStarD.h"
#include "cost/AStarH.h"
#include "goal/IsGoalReached.h"
#include "neighbors/GetNeighbors.h"
#include "node/AStarEncode.h"
#include "reconstruct/ReconstructPath.h"
#include <SDL3/SDL.h>
#include <shared_mutex>

template<uint32_t N>
int runAStar(
    AStarContext<N>& astar,
    uint32_t astarIndex,
    Context& ctx,
    int npcIndex,
    const SDL_FRect& moverBox,
    const SDL_FPoint& moverCenter,
    const SDL_FRect& destCol,
    int targetNpcIndex,
    bool isPlayerBlocking,
    int* pathOut)
{
    static const int MAX_NEIGHBORS = 8;

    Uint64 startTime = SDL_GetTicks();
    defer({
        ctx.data.fps.astarTime = SDL_GetTicks() - startTime;
        calcEma(ctx.data.fps.astarTime, ctx.data.fps.avgAstarTime);
    });
    astar.status[astarIndex].store(AStarStatus::CALCULATING_PATH, std::memory_order_relaxed);

    {
        std::shared_lock lock(ctx.collision.spatialHashMutex);
        copySpatialHash(astar.colHashSnapshot, astarIndex, ctx.collision.spatialHash, 0);
    }

    SDL_FPoint startCenter = moverCenter;

    astar.generation[astarIndex]++;
    SDL_FPoint goalCenter = entityColCenter(destCol);

    int minX = (int)SDL_min(startCenter.x, goalCenter.x) - ASTAR_SEARCH_PAD;
    int minY = (int)SDL_min(startCenter.y, goalCenter.y) - ASTAR_SEARCH_PAD;
    int maxX = (int)SDL_max(startCenter.x, goalCenter.x) + ASTAR_SEARCH_PAD;
    int maxY = (int)SDL_max(startCenter.y, goalCenter.y) + ASTAR_SEARCH_PAD;

    astar.searchX[astarIndex] = minX;
    astar.searchY[astarIndex] = minY;
    astar.searchW[astarIndex] = maxX - minX + 1;
    astar.searchH[astarIndex] = maxY - minY + 1;

    int startNode = astarEncode(astar, astarIndex, { (int)startCenter.x, (int)startCenter.y });

    astar.fscoreHeap.size[astarIndex] = 0;

    float h = astarH(astar, astarIndex, startNode, goalCenter);
    hashMapInsert(astar.gscores, astarIndex, startNode, astar.generation[astarIndex], 0.0f);
    minHeapPush(astar.fscoreHeap, astarIndex, startNode, h);

    while (!minHeapEmpty(astar.fscoreHeap, astarIndex))
    {
        int current = minHeapPop(astar.fscoreHeap, astarIndex);

        if (hashMapContains(astar.closed, astarIndex, current, astar.generation[astarIndex]))
            continue;

        hashMapInsert(astar.closed, astarIndex, current, astar.generation[astarIndex]);

        if (isGoalReached(
                astar,
                astarIndex,
                moverBox,
                moverCenter,
                destCol,
                current))
        {
            int length = reconstructPath(astar, astarIndex, current, goalCenter, pathOut);
            astar.status[astarIndex].store(AStarStatus::FINISHED_CALCULATING, std::memory_order_relaxed);
            return length;
        }

        int neighbors[MAX_NEIGHBORS];
        int count = getNeighbors(
            astar,
            astarIndex,
            ctx,
            current,
            moverBox,
            moverCenter,
            npcIndex,
            targetNpcIndex,
            isPlayerBlocking,
            neighbors);

        float gCurrent;
        if (!hashMapTryGet(astar.gscores, astarIndex, current, astar.generation[astarIndex], gCurrent))
            continue;

        for (int i = 0; i < count; i++)
        {
            int nb = neighbors[i];
            if (hashMapContains(astar.closed, astarIndex, nb, astar.generation[astarIndex]))
                continue;

            float tentativeG = gCurrent + astarD(astar, astarIndex, current, nb);

            float existingG;
            if (hashMapTryGet(astar.gscores, astarIndex, nb, astar.generation[astarIndex], existingG) &&
                tentativeG >= existingG)
                continue;

            hashMapInsert(astar.gscores, astarIndex, nb, astar.generation[astarIndex], tentativeG);
            hashMapInsert(astar.cameFrom, astarIndex, nb, astar.generation[astarIndex], current);
            minHeapPush(astar.fscoreHeap, astarIndex, nb, tentativeG + astarH(astar, astarIndex, nb, goalCenter));
        }
    }

    astar.status[astarIndex].store(AStarStatus::PATH_NOT_FOUND, std::memory_order_relaxed);
    return INVALID_ID;
}
