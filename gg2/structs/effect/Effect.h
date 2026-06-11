#pragma once
#include <cstdint>
#include "../core/EntityBase.h"
#include "../core/Target.h"
#include "EffectConstants.h"
#include "ParentType.h"
#include "../../utils/pool/Pool.h"

struct Effect
{
    Pool<MAX_EFFECTS> pool;
    int groupId[MAX_EFFECTS] = {};
    ParentType parentType[MAX_EFFECTS] = {};
    int parentIndex[MAX_EFFECTS] = {};
    EntityBase<MAX_EFFECTS> base;
    Target<MAX_EFFECTS> target;
};
