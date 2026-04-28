#pragma once
#include "AStarHeap.h"
#include "AStarStatus.h"
#include "../../../utils/hashmap/HashMap.h"
#include "../../core/Constants.h"
#include <future>

struct AStarContext
{
    AStarHeap                        fscoreHeap;
    HashMap<void,  ASTAR_HASH_SIZE>  closed;
    HashMap<float, ASTAR_HASH_SIZE>  gscores;
    HashMap<int,   ASTAR_HASH_SIZE>  cameFrom;

    int          generation;
    int          offsetX;
    int          offsetY;
    AStarStatus  status;
    std::future<void> future;
};
