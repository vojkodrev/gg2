#pragma once
#include "Pool.h"
#include <cstdint>

template<int NItems, uint32_t NSlots>
void resetPool(Pool<NItems, NSlots> &pool, uint32_t n)
{
    pool.count[n] = 0;
    pool.freeQueue.head[n] = 0;
    pool.freeQueue.tail[n] = 0;

    for (uint32_t i = 0; i < NSlots; i++)
    {
        pool.active[n][i] = false;
        pool.freeQueue.data[n][i] = 0;
    }
}
