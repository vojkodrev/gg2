#pragma once
#include "AStarHeap.h"
#include "AStarClosedSet.h"
#include "AStarGScoreMap.h"

struct AStarContext
{
    AStarHeap      heap;
    AStarClosedSet closed;
    AStarGScoreMap gscores;

    int generation;
    int offsetX;
    int offsetY;
};
