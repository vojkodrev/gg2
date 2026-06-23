#pragma once
#include "../core/EntityBase.h"
#include "EffectConstants.h"
#include "EffectTemplateType.h"

struct EffectTemplate
{
    EffectTemplateType type[MAX_EFFECTS] = {};
    EntityBase<MAX_EFFECTS> base;
};
