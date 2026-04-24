#include "AStarAlloc.h"
#include "QueueEmpty.h"
#include "QueueDequeue.h"

int astarAlloc(AStarPool& pool)
{
    if (!queueEmpty(pool))
        return queueDequeue(pool);

    if (pool.count >= MAX_ASTARS)
        return -1;

    return pool.count++;
}
