#pragma once
#include "Pool.h"
#include "../../structs/core/constants/IndexConstants.h"
#include "../queue/QueueDequeue.h"
#include "../queue/QueueEmpty.h"

template<uint32_t TCapacity>
int poolAlloc(Pool<TCapacity>& pool)
{
    if (!queueEmpty(pool.freeQueue))
    {
        int index = queueDequeue(pool.freeQueue);
        if (pool.active[index])
            return INVALID_ID;

        pool.active[index] = true;
        if ((uint32_t)(index + 1) > pool.count)
            pool.count = (uint32_t)(index + 1);
        return index;
    }

    if (pool.count >= TCapacity)
        return INVALID_ID;

    int index = (int)pool.count++;
    pool.active[index] = true;
    return index;
}
