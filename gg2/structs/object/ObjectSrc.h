#pragma once
#include <cstdint>
#include "constants.h"

struct ObjectSrc
{
    uint32_t x[MAX_OBJECTS];
    uint32_t y[MAX_OBJECTS];
    uint32_t w[MAX_OBJECTS];
    uint32_t h[MAX_OBJECTS];
};
