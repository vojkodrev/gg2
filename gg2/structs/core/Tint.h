#pragma once

template<int N>
struct Tint
{
    float r[N];
    float g[N];
    float b[N];
    float a[N];
    float damageTimer[N];
    bool isPoisoned[N];
    bool isSlowed[N];
};
