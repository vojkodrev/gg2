#pragma once
#include "../core/EntityBase.h"
#include "EffectConstants.h"

struct EffectTemplate
{
    int fontOffset = 0;
    int selectOffset = 0;
    int bloodSplatterOffset = 0;
    EntityBase<MAX_EFFECTS> base;
};
