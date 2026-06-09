#pragma once
#include <cstdint>
#include "../core/EntityBase.h"
#include "../core/Target.h"
#include "../../utils/queue/Queue.h"
#include "EffectConstants.h"

struct Effect
{
    uint32_t effectCount;
    EntityBase<MAX_EFFECTS> base;
    Target<MAX_EFFECTS> target;
    bool active[MAX_EFFECTS];
    Queue<int, MAX_EFFECTS> freeQueue;
};
