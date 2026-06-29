#pragma once
#include "Context.h"
#include "../../../structs/effect/ProjectileType.h"

int spawnPlayerTargetedProjectileEffect(
    Context &ctx,
    const EntityBase<1> &projectileBase,
    ProjectileType projectileType,
    int npcIndex,
    float tintR,
    float tintG,
    float tintB,
    float tintA);
