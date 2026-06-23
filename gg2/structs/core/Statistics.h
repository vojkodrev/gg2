#pragma once

template<int N>
struct Statistics
{
    int prevHp[N] = {};
    int hp[N] = {};
    bool hpDirty[N] = {};
    int maxHp[N] = {};
};
