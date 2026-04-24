#include "AStarFree.h"

static void queueEnqueue(AStarPool& pool, int index)
{
    pool.freeQueue[pool.freeTail] = index;
    pool.freeTail = (pool.freeTail + 1) & (MAX_ASTARS - 1);
}

void astarFree(AStarPool& pool, int index)
{
    queueEnqueue(pool, index);
}
