#pragma once
#include "Context.h"

int spawnPlayerTargetedProjectileEffect(
    Context &ctx,
    const EntityBase<1> &projectileBase,
    int npcIndex,
    float tintR,
    float tintG,
    float tintB,
    float tintA);
