#pragma once
#include "Queue.h"

template<typename TValue, int NItems, uint32_t NSlots>
bool queueEmpty(const Queue<TValue, NItems, NSlots>& q, uint32_t n)
{
    return q.head[n] == q.tail[n];
}
