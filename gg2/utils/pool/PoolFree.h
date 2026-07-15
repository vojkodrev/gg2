#pragma once
#include "Pool.h"
#include "../queue/QueueEnqueue.h"

template<int NItems, uint32_t NSlots>
void poolFree(Pool<NItems, NSlots>& pool, uint32_t n, int index)
{
    if (!pool.active[n][index])
        return;

    pool.active[n][index] = false;

    if ((uint32_t)(index + 1) == pool.count[n])
    {
        while (pool.count[n] > 0 && !pool.active[n][pool.count[n] - 1])
            pool.count[n]--;
        return;
    }

    queueEnqueue(pool.freeQueue, n, index);
}
