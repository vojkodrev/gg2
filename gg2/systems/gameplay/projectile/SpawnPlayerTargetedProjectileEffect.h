#pragma once
#include <SDL3/SDL.h>
#include "Context.h"
#include "../../../structs/effect/ProjectileType.h"

int spawnPlayerTargetedProjectileEffect(
    Context &ctx,
    const EntityBase<1> &projectileBase,
    ProjectileType projectileType,
    int npcIndex,
    SDL_FColor tint);
