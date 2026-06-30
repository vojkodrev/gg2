#pragma once
#include <cstdint>

template<typename TValue, uint32_t TSize>
struct Queue
{
    TValue   data[TSize];
    uint32_t head = 0;
    uint32_t tail = 0;
};
