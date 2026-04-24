#pragma once
#include "../../core/Constants.h"

struct AStarHeap
{
    int   nodes[ASTAR_HEAP_SIZE];
    float fscores[ASTAR_HEAP_SIZE];
    int   size;
};
