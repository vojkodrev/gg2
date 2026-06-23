#pragma once
#include "Context.h"
#include "ColIdType.h"

void resolveProjectileEffectCollision(
    Context &ctx,
    uint32_t effectIndex,
    uint32_t otherId,
    ColType otherType);
