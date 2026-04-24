#pragma once
#include "AStarHeap.h"
#include "../../../utils/hashmap/HashMap.h"
#include "../../core/Constants.h"

struct AStarContext
{
    AStarHeap                        heap;
    HashMap<void,  ASTAR_HASH_SIZE>  closed;
    HashMap<float, ASTAR_HASH_SIZE>  gscores;
    HashMap<int,   ASTAR_HASH_SIZE>  cameFrom;

    int path[ASTAR_MAX_PATH];
    int       pathLen;

    int generation;
    int offsetX;
    int offsetY;
};
