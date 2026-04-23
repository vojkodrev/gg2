#pragma once
#include "AStarContext.h"
#include "../../core/Constants.h"

struct AStarPool
{
    AStarContext ctx[MAX_ASTARS];
    int          count;
    int          freeQueue[MAX_ASTARS];
    int          freeHead;
    int          freeTail;
};
