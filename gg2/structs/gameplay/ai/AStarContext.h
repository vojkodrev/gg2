#pragma once
#include "AStarStatus.h"
#include "../../../utils/hashmap/HashMap.h"
#include "../../../utils/minheap/MinHeap.h"
#include "../../core/Constants.h"
#include "../../collision/SpatialHash.h"
#include <future>

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
    AStarStatus  status;
    std::future<void> future;
};
