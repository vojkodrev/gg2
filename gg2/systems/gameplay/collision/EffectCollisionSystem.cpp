#include "EffectCollisionSystem.h"
#include <shared_mutex>
#include "CollectCollisionPairsForEntity.h"
#include "EntityColAABB.h"
#include "ColIdMake.h"
#include "spatialhash/SpatialHashInsert.h"

void effectCollisionSystem(Context &ctx)
{
    auto &effect = ctx.data.effect;
    ctx.collision.effectCollisions.count = 0;

    {
        std::unique_lock lock(ctx.collision.spatialHashMutex);
        for (uint32_t i = 0; i < effect.pool.count; i++)
        {
            if (!effect.pool.active[i])
                continue;

            spatialHashInsert(
                ctx.collision.spatialHash,
                entityColAABB(effect.base, i),
                colIdMake(ColType::Effect, i));
        }
    }

    std::shared_lock readLock(ctx.collision.spatialHashMutex);
    for (uint32_t i = 0; i < effect.pool.count; i++)
    {
        if (!effect.pool.active[i])
            continue;

        collectCollisionPairsForEntity(
            ctx.collision.effectCollisions,
            ctx,
            colIdMake(ColType::Effect, i),
            entityColAABB(effect.base, i),
            false);
    }
}
