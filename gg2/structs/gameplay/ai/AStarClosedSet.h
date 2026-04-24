#pragma once
#include "../../core/Constants.h"

struct AStarClosedSet
{
    int node[ASTAR_HASH_SIZE];
    int gen[ASTAR_HASH_SIZE];
};
