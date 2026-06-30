#pragma once

template<int N>
struct Mana
{
    int mana[N] = {};
    bool dirty[N] = {};
    int maxMana[N] = {};
};
