#pragma once
#include <SDL3/SDL.h>
#include "Context.h"
#include "../../../structs/entity/EntityType.h"
#include "../../../structs/effect/ProjectileType.h"

int createTargetedProjectileEffect(
    Context &ctx,
    EntityType parentType,
    int parentId,
    EntityType targetType,
    int targetId,
    ProjectileType projectileType,
    SDL_FColor tint);
