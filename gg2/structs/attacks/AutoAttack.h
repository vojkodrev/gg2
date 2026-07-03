#pragma once

template<int N>
struct AutoAttack
{
    float attackTimer[N] = {};
    bool active[N] = {};
};
