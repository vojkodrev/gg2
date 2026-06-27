#pragma once
#include <cstdint>
#include "../core/EntityBase.h"
#include "../core/AnchorPoint.h"
#include "DestroyEffectType.h"
#include "EffectConstants.h"
#include "EffectType.h"
#include "Parent.h"
#include "../../utils/pool/Pool.h"

struct Effect
{
    Pool<MAX_EFFECTS> pool;
    int groupId[MAX_EFFECTS] = {};
    EffectType type[MAX_EFFECTS] = {};
    DestroyEffectType destroyType[MAX_EFFECTS] = {};
    float destroyTimer[MAX_EFFECTS] = {};
    Parent<MAX_EFFECTS> parent;
    EntityBase<MAX_EFFECTS> base;
    AnchorPoint<MAX_EFFECTS> start;
    AnchorPoint<MAX_EFFECTS> target;
};
