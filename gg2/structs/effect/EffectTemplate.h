#pragma once
#include "../entity/EntityBase.h"
#include "EffectConstants.h"

struct EffectTemplate
{
    int fontIndex = 0;
    int selectIndex = 0;
    int bloodSplatterIndex = 0;
    int tauntIndex = 0;
    int frostNovaIndex = 0;
    int arcaneExplosionIndex = 0;
    int frostCastIndex = 0;
    EntityBase<MAX_EFFECTS> base;
};
