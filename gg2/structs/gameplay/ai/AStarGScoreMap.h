#pragma once
#include "../../core/Constants.h"

struct AStarGScoreMap
{
    int   node[ASTAR_HASH_SIZE];
    int   gen[ASTAR_HASH_SIZE];
    float gscore[ASTAR_HASH_SIZE];
};
