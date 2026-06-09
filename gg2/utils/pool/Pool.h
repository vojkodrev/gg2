#pragma once
#include <cstdint>
#include "../queue/Queue.h"

template<uint32_t TCapacity>
struct Pool
{
    uint32_t count = 0;
    bool active[TCapacity];
    Queue<int, TCapacity> freeQueue;
};
