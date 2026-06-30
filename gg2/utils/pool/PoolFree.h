#pragma once
#include "Pool.h"
#include "../queue/QueueEnqueue.h"

template<uint32_t TCapacity>
void poolFree(Pool<TCapacity>& pool, int index)
{
    if (!pool.active[index])
        return;

    pool.active[index] = false;

    if ((uint32_t)(index + 1) == pool.count)
    {
        while (pool.count > 0 && !pool.active[pool.count - 1])
            pool.count--;
        return;
    }

    queueEnqueue(pool.freeQueue, index);
}
