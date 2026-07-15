#pragma once
#include <cstdint>

template<typename TValue, int NItems, uint32_t NSlots>
struct Queue
{
    TValue   data[NItems][NSlots];
    uint32_t head[NItems] = {};
    uint32_t tail[NItems] = {};
};
