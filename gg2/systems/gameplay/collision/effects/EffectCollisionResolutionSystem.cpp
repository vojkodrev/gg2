#include "EffectCollisionResolutionSystem.h"
#include "ColIdIndex.h"
#include "ColIdType.h"
#include "ResolveProjectileEffectCollision.h"
#include "../../../structs/effect/EffectType.h"

void effectCollisionResolutionSystem(Context &ctx)
{
    auto &cr = ctx.collision.effectCollisions;
    auto &effect = ctx.data.effect;

    for (uint32_t k = 0; k < cr.count; k++)
    {
        const uint32_t idA = cr.pair.a[k];
        const uint32_t idB = cr.pair.b[k];
        const ColType typeA = colIdType(idA);
        const ColType typeB = colIdType(idB);

        uint32_t effectId = 0;
        uint32_t otherId = 0;
        ColType otherType;

        if (typeA == ColType::Effect)
        {
            effectId = idA;
            otherId = idB;
            otherType = typeB;
        }
        else if (typeB == ColType::Effect)
        {
            effectId = idB;
            otherId = idA;
            otherType = typeA;
        }
        else
            continue;

        const uint32_t effectIndex = colIdIndex(effectId);
        if (!effect.pool.active[effectIndex])
            continue;

        switch (effect.type[effectIndex])
        {
            case EffectType::Projectile:
                resolveProjectileEffectCollision(ctx, effectIndex, otherId, otherType);
                break;
            default:
                break;
        }
    }
}
