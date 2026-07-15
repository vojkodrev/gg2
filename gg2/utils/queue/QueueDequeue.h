#pragma once
#include "Queue.h"

template<typename TValue, int NItems, uint32_t NSlots>
TValue queueDequeue(Queue<TValue, NItems, NSlots>& q, uint32_t n)
{
    TValue value = q.data[n][q.head[n]];
    q.head[n]++;
    if (q.head[n] == NSlots)
        q.head[n] = 0;
    return value;
}
