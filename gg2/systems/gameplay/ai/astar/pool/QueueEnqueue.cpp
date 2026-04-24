#include "QueueEnqueue.h"

void queueEnqueue(AStarPool& pool, int index)
{
    pool.freeQueue[pool.freeTail] = index;
    pool.freeTail = (pool.freeTail + 1) & (MAX_ASTARS - 1);
}
