#pragma once
#include <cstdint>
#include "../../utils/pool/Pool.h"

template<uint32_t TCapacity>
struct Groups
{
    Pool<TCapacity> pool;
    uint32_t count[TCapacity] = {};
};
