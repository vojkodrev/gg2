#pragma once
#include "Queue.h"

template<typename TValue, int NItems, uint32_t NSlots>
void queueEnqueue(Queue<TValue, NItems, NSlots>& q, uint32_t n, TValue value)
{
    q.data[n][q.tail[n]] = value;
    q.tail[n]++;
    if (q.tail[n] == NSlots)
        q.tail[n] = 0;
}
