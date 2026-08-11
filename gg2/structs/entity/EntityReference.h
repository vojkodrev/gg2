#pragma once
#include "EntityType.h"

template<int N>
struct EntityReference
{
    EntityType type[N] = {};
    int id[N] = {};
};
