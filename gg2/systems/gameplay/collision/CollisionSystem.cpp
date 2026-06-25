#include "CollisionSystem.h"
#include <shared_mutex>
#include "CollectCollisionPairsForEntity.h"
#include "CollisionConstants.h"
#include "EntityColAABB.h"
#include "ColIdMake.h"
#include "spatialhash/SpatialHashClear.h"
#include "spatialhash/SpatialHashInsert.h"

void collisionSystem(Context &ctx)
{
    ctx.collision.collisions.count = 0;

    auto &npc = ctx.data.npc;
    auto &object = ctx.data.object;
    auto &player = ctx.data.player;

    SDL_FRect pBox = entityColAABB(player.base, 0);
    {
        std::unique_lock lock(ctx.collision.spatialHashMutex);
        spatialHashClear(ctx.collision.spatialHash, 0);

        spatialHashInsert(ctx.collision.spatialHash, 0, pBox, colIdMake(ColType::Player, 0));

        for (uint32_t i = 0; i < MAX_NPCS; i++)
        {
            if (!npc.active[i])
                continue;
            spatialHashInsert(
                ctx.collision.spatialHash,
                0,
                entityColAABB(npc.base, i),
                colIdMake(ColType::NPC, i));
        }

        for (uint32_t i = 0; i < object.objectCount; i++)
            spatialHashInsert(
                ctx.collision.spatialHash,
                0,
                entityColAABB(object.base, i),
                colIdMake(ColType::Object, i));
    }

    std::shared_lock readLock(ctx.collision.spatialHashMutex);

    collectCollisionPairsForEntity(ctx.collision.collisions, ctx, colIdMake(ColType::Player, 0), pBox, true);
    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!npc.active[i])
            continue;
        collectCollisionPairsForEntity(
            ctx.collision.collisions,
            ctx,
            colIdMake(ColType::NPC, i),
            entityColAABB(npc.base, i),
            true);
    }
    for (uint32_t i = 0; i < object.objectCount; i++)
        collectCollisionPairsForEntity(
            ctx.collision.collisions,
            ctx,
            colIdMake(ColType::Object, i),
            entityColAABB(object.base, i),
            true);
}
