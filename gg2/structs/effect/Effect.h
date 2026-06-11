#pragma once
#include <cstdint>
#include "../core/EntityBase.h"
#include "../core/Target.h"
#include "EffectConstants.h"
#include "Parent.h"
#include "../../utils/pool/Pool.h"

struct Effect
{
    Pool<MAX_EFFECTS> pool;
    int groupId[MAX_EFFECTS] = {};
    Parent<MAX_EFFECTS> parent;
    EntityBase<MAX_EFFECTS> base;
    Target<MAX_EFFECTS> target;
};
