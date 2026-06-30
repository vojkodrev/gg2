#pragma once
#include "Queue.h"

template<typename TValue, uint32_t TSize>
void queueEnqueue(Queue<TValue, TSize>& q, TValue value)
{
    q.data[q.tail] = value;
    q.tail++;
    if (q.tail == TSize)
        q.tail = 0;
}
