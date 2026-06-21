#pragma once

template<int N>
struct Statistics
{
    int hp[N] = {};
    bool hpDirty[N] = {};
    int maxHp[N] = {};
};
