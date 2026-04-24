#pragma once
#include <SDL3/SDL.h>
#include "AStarHeap.h"
#include "../../../utils/hashmap/HashMap.h"
#include "../../core/Constants.h"

struct AStarContext
{
    AStarHeap                        heap;
    HashMap<void,  ASTAR_HASH_SIZE>  closed;
    HashMap<float, ASTAR_HASH_SIZE>  gscores;
    HashMap<int,   ASTAR_HASH_SIZE>  cameFrom;

    SDL_Point path[ASTAR_MAX_PATH];
    int       pathLen;

    int generation;
    int offsetX;
    int offsetY;
};
