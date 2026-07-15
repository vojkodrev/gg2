#pragma once
#include <cstdint>
#include "../queue/Queue.h"

template<int NItems, uint32_t NSlots>
struct Pool
{
    uint32_t count[NItems] = {};
    bool active[NItems][NSlots] = {};
    Queue<int, NItems, NSlots> freeQueue;
};
