#include "QueueEmpty.h"

bool queueEmpty(const AStarPool& pool)
{
    return pool.freeHead == pool.freeTail;
}
