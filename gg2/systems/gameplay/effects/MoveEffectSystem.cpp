#include "MoveEffectSystem.h"
#include "../../../structs/core/constants/ProjectileConstants.h"
#include "../../../structs/effect/EffectType.h"
#include "../../../utils/entity/MoveEntityColCenterToward.h"
#include <cstdint>

void moveEffectSystem(Context &ctx)
{
    for (uint32_t i = 0; i < ctx.data.effect.pool.count; i++)
    {
        if (!ctx.data.effect.pool.active[i])
            continue;

        if (ctx.data.effect.type[i] == EffectType::Projectile)
        {
            moveEntityColCenterToward(
                ctx,
                ctx.data.effect.base,
                i,
                ctx.data.effect.target,
                i,
                PROJECTILE_SPEED);
        }
    }
}
