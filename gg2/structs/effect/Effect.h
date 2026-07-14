#pragma once
#include <cstdint>
#include "../core/EntityBase.h"
#include "../core/EntityReference.h"
#include "DestroyEffectType.h"
#include "EffectConstants.h"
#include "EffectType.h"
#include "ProjectileType.h"
#include "../../utils/pool/Pool.h"

struct Effect
{
    Pool<1, MAX_EFFECTS> pool;
    int groupId[MAX_EFFECTS] = {};
    EffectType type[MAX_EFFECTS] = {};
    ProjectileType projectileType[MAX_EFFECTS] = {};
    DestroyEffectType destroyType[MAX_EFFECTS] = {};
    float destroyTimer[MAX_EFFECTS] = {};
    EntityReference<MAX_EFFECTS> parent;
    EntityReference<MAX_EFFECTS> target;
    EntityBase<MAX_EFFECTS> base;
};
