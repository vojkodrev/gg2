#pragma once
#include "Queue.h"

template<typename TValue, uint32_t TSize>
bool queueEmpty(const Queue<TValue, TSize>& q)
{
    return q.head == q.tail;
}
