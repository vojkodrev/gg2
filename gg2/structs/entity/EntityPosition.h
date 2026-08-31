#pragma once

template<int N>
struct EntityPosition
{
    float x[N];
    float y[N];
    float initialW[N];
    float initialH[N];
    float w[N];
    float h[N];
    bool absolute[N] = {};
    bool dirty[N];
    bool inputMovement[N] = {};
};
