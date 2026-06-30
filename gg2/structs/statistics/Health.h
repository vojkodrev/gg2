#pragma once

template<int N>
struct Health
{
    int prevHp[N] = {};
    int hp[N] = {};
    bool dirty[N] = {};
    int maxHp[N] = {};
};
