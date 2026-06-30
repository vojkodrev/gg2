#pragma once
#include "Queue.h"

template<typename TValue, uint32_t TSize>
TValue queueDequeue(Queue<TValue, TSize>& q)
{
    TValue value = q.data[q.head];
    q.head++;
    if (q.head == TSize)
        q.head = 0;
    return value;
}
