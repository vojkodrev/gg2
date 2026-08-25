#pragma once
#include "../../entity/EntityBase.h"

template<int NEntities>
struct ActionBarIcon
{
    bool active[NEntities] = {};
    int zIndex[NEntities] = {};
    EntityBase<NEntities> base;
};
