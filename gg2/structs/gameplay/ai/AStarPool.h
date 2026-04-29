#pragma once
#include "AStarContext.h"
#include "../../../utils/queue/Queue.h"
#include "../../core/Constants.h"

struct AStarPool
{
    AStarContext         ctx[MAX_ASTARS];
    int                  count;
    Queue<int, MAX_ASTARS> freeQueue;
};
