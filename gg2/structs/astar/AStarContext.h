#pragma once
#include "AStarStatus.h"
#include "../../utils/hashmap/HashMap.h"
#include "../../utils/minheap/MinHeap.h"
#include "../core/constants/AStarConstants.h"
#include "../../utils/collision/spatialhash/SpatialHash.h"
#include <future>
#include <atomic>

template<uint32_t N>
struct AStarContext
{
    MinHeap<N, ASTAR_HEAP_SIZE, float>  fscoreHeap;
    HashMap<N, ASTAR_HASH_SIZE, void>   closed;
    HashMap<N, ASTAR_HASH_SIZE, float>  gscores;
    HashMap<N, ASTAR_HASH_SIZE, int>    cameFrom;

    SpatialHash<N>  colHashSnapshot;

    int generation[N] = {};
    int searchX[N] = {};
    int searchY[N] = {};
    int searchW[N] = {};
    int searchH[N] = {};
    std::atomic<AStarStatus> status[N];
    std::future<void> future[N];
};
