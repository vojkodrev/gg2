#include "DestroyEffectSystem.h"
#include "../../../structs/core/constants/ProjectileConstants.h"
#include "../../../structs/effect/EffectType.h"
#include "../../../utils/collision/EntityColAABB.h"
#include "../../../utils/collision/EntityColCenter.h"
#include "../../../utils/effects/EffectFree.h"
#include "../../../utils/math/Dist.h"
#include <cstdint>

void destroyEffectSystem(Context &ctx)
{
    for (uint32_t i = 0; i < ctx.data.effect.pool.count; i++)
    {
        if (!ctx.data.effect.pool.active[i])
            continue;

        if (ctx.data.effect.type[i] != EffectType::Projectile)
            continue;

        const SDL_FPoint effectColCenter =
            entityColCenter(entityColAABB(ctx.data.effect.base, i));
        const float distFromStart =
            dist(
                effectColCenter.x,
                effectColCenter.y,
                ctx.data.effect.start.x[i],
                ctx.data.effect.start.y[i]);

        if (distFromStart >= PROJECTILE_MAX_DISTANCE)
            effectFree(ctx.data.effect, ctx.data.groups, i);
    }
}
