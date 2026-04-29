#pragma once
#include "Queue.h"

template<typename TValue, uint32_t TSize>
TValue queueDequeue(Queue<TValue, TSize>& q)
{
    TValue value = q.data[q.head];
    q.head = (q.head + 1) & (TSize - 1);
    return value;
}
