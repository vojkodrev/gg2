#pragma once
#include "../../entity/EntityBase.h"

template<int NEntities>
struct ActionBarIcon
{
    bool active[NEntities] = {};
    EntityBase<NEntities> base;
};
