#pragma once
#include "Pool.h"
#include "../../structs/core/constants/IndexConstants.h"
#include "../queue/QueueDequeue.h"
#include "../queue/QueueEmpty.h"

template<int NItems, uint32_t NSlots>
int poolAlloc(Pool<NItems, NSlots>& pool, uint32_t n)
{
    if (!queueEmpty(pool.freeQueue, n))
    {
        int index = queueDequeue(pool.freeQueue, n);
        if (pool.active[n][index])
            return INVALID_ID;

        pool.active[n][index] = true;
        if ((uint32_t)(index + 1) > pool.count[n])
            pool.count[n] = (uint32_t)(index + 1);
        return index;
    }

    if (pool.count[n] >= NSlots)
        return INVALID_ID;

    int index = (int)pool.count[n]++;
    pool.active[n][index] = true;
    return index;
}
