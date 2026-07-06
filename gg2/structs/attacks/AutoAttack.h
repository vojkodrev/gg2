#pragma once

template<int N>
struct AutoAttack
{
    float attackTimer[N] = {};
    float hitTimer[N] = {};
    bool active[N] = {};
};
