#include "MoveProjectileSystem.h"
#include "../../../utils/entity/MoveEntityColCenterToward.h"
#include "../../../structs/core/constants/EffectConstants.h"
#include <cstdint>

void moveProjectileSystem(Context &ctx)
{
    for (uint32_t i = 0; i < ctx.data.effect.pool.count; i++)
    {
        if (!ctx.data.effect.pool.active[i])
            continue;

        moveEntityColCenterToward(
            ctx,
            ctx.data.effect.base,
            i,
            ctx.data.effect.target,
            i,
            PROJECTILE_SPEED);
    }
}
