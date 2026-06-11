#pragma once
#include "ParentType.h"

template<int N>
struct Parent
{
    ParentType type[N] = {};
    int id[N] = {};
};
