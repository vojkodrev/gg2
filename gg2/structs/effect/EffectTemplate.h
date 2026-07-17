#pragma once
#include "../core/EntityBase.h"
#include "EffectConstants.h"

struct EffectTemplate
{
    int fontIndex = 0;
    int selectIndex = 0;
    int bloodSplatterIndex = 0;
    int tauntIndex = 0;
    EntityBase<MAX_EFFECTS> base;
};
