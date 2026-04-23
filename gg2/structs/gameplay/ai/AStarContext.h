#pragma once
#include <cfloat>

const int ASTAR_SEARCH_R  = 200;
const int ASTAR_SEARCH_D  = ASTAR_SEARCH_R * 2 + 1;
const int ASTAR_HEAP_SIZE = 65536;
const int ASTAR_HASH_SIZE = 65536;  // power of 2, keep load < 50%

struct AStarHeap
{
    int   nodes[ASTAR_HEAP_SIZE];
    float fscores[ASTAR_HEAP_SIZE];
    int   size;
};

struct AStarClosedSet
{
    int node[ASTAR_HASH_SIZE];
    int gen[ASTAR_HASH_SIZE];
};

struct AStarGScoreMap
{
    int   node[ASTAR_HASH_SIZE];
    int   gen[ASTAR_HASH_SIZE];
    float gscore[ASTAR_HASH_SIZE];
};

struct AStarContext
{
    AStarHeap      heap;
    AStarClosedSet closed;
    AStarGScoreMap gscores;

    int generation;
    int offsetX;
    int offsetY;
};
