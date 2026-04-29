#pragma once
#include <cstdint>

template<typename TValue, uint32_t TSize>
struct Queue
{
    TValue   data[TSize];
    uint32_t head;
    uint32_t tail;
};
