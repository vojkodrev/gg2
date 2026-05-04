#pragma once
#include "AStarStatus.h"
#include "../../../utils/hashmap/HashMap.h"
#include "../../../utils/minheap/MinHeap.h"
#include "AStarConstants.h"
#include "spatialhash/SpatialHash.h"
#include <future>
#include <atomic>

struct AStarContext
{
    MinHeap<float, ASTAR_HEAP_SIZE>  fscoreHeap;
    HashMap<void,  ASTAR_HASH_SIZE>  closed;
    HashMap<float, ASTAR_HASH_SIZE>  gscores;
    HashMap<int,   ASTAR_HASH_SIZE>  cameFrom;

    SpatialHash  colHashSnapshot;

    int          generation;
    int          searchX;
    int          searchY;
    int          searchW;
    int          searchH;
    std::atomic<AStarStatus>  status;
    std::future<void> future;
};
