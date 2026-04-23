#include "AStarPool.h"

static bool queueEmpty(const AStarPool& pool)
{
    return pool.freeHead == pool.freeTail;
}

static int queueDequeue(AStarPool& pool)
{
    int idx = pool.freeQueue[pool.freeHead];
    pool.freeHead = (pool.freeHead + 1) & (MAX_ASTARS - 1);
    return idx;
}

static void queueEnqueue(AStarPool& pool, int index)
{
    pool.freeQueue[pool.freeTail] = index;
    pool.freeTail = (pool.freeTail + 1) & (MAX_ASTARS - 1);
}

int astarAlloc(AStarPool& pool)
{
    if (!queueEmpty(pool))
        return queueDequeue(pool);

    if (pool.count >= MAX_ASTARS)
        return -1;

    return pool.count++;
}

void astarFree(AStarPool& pool, int index)
{
    queueEnqueue(pool, index);
}
