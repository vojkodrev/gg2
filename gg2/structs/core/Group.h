#pragma once

#include <cstdint>

template<uint32_t TCapacity>
struct Group
{
    int id[TCapacity] = {};
};
