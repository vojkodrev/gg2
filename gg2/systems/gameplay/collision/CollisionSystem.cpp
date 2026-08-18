#include "CollisionSystem.h"
#include <shared_mutex>
#include "CollectCollisionPairsForEntity.h"
#include "CollisionConstants.h"
#include "MainEntityColAABB.h"
#include "ColIdMake.h"
#include "spatialhash/SpatialHashClear.h"
#include "spatialhash/SpatialHashInsert.h"

void collisionSystem(Context &ctx)
{
    ctx.collision.collisions.count = 0;

    auto &npc = ctx.data.npc;
    auto &object = ctx.data.object;
    auto &player = ctx.data.player;

    SDL_FRect pBox = mainEntityColAABB(player.base, 0);
    {
        std::unique_lock lock(ctx.collision.spatialHashMutex);
        spatialHashClear(ctx.collision.spatialHash, 0);

        spatialHashInsert(ctx.collision.spatialHash, 0, pBox, colIdMake(ColType::Player, 0));

        for (uint32_t entityIndex = 0;
            entityIndex < MAX_NPCS;
            entityIndex++)
        {
            if (!npc.active[entityIndex])
                continue;
            spatialHashInsert(
                ctx.collision.spatialHash,
                0,
                mainEntityColAABB(npc.base, entityIndex),
                colIdMake(ColType::NPC, entityIndex));
        }

        for (uint32_t entityIndex = 0;
            entityIndex < object.objectCount;
            entityIndex++)
            spatialHashInsert(
                ctx.collision.spatialHash,
                0,
                mainEntityColAABB(object.base, entityIndex),
                colIdMake(ColType::Object, entityIndex));
    }

    std::shared_lock readLock(ctx.collision.spatialHashMutex);

    collectCollisionPairsForEntity(ctx.collision.collisions, ctx, colIdMake(ColType::Player, 0), pBox, true);
    for (uint32_t entityIndex = 0;
        entityIndex < MAX_NPCS;
        entityIndex++)
    {
        if (!npc.active[entityIndex])
            continue;
        collectCollisionPairsForEntity(
            ctx.collision.collisions,
            ctx,
            colIdMake(ColType::NPC, entityIndex),
            mainEntityColAABB(npc.base, entityIndex),
            true);
    }
    for (uint32_t entityIndex = 0;
        entityIndex < object.objectCount;
        entityIndex++)
        collectCollisionPairsForEntity(
            ctx.collision.collisions,
            ctx,
            colIdMake(ColType::Object, entityIndex),
            mainEntityColAABB(object.base, entityIndex),
            true);
}
