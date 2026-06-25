#pragma once
#include "../core/EntityBase.h"
#include "EffectConstants.h"

struct EffectTemplate
{
    int fontOffset = 0;
    EntityBase<MAX_EFFECTS> base;
};
