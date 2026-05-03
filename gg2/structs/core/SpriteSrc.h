#pragma once
#include <cstdint>

template<int N>
struct SpriteSrc
{
    uint32_t x[N];
    uint32_t y[N];
    uint32_t w[N];
    uint32_t h[N];
};
