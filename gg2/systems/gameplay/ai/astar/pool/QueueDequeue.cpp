#include "QueueDequeue.h"

int queueDequeue(AStarPool& pool)
{
    int idx = pool.freeQueue[pool.freeHead];
    pool.freeHead = (pool.freeHead + 1) & (MAX_ASTARS - 1);
    return idx;
}
