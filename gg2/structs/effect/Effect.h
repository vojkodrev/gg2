#pragma once
#include <cstdint>
#include "../core/EntityBase.h"
#include "../../utils/queue/Queue.h"
#include "EffectConstants.h"

struct Effect
{
    uint32_t effectCount;
    EntityBase<MAX_EFFECTS> base;
    bool active[MAX_EFFECTS];
    Queue<int, MAX_EFFECTS> freeQueue;
};
