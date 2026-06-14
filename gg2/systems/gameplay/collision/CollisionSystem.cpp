#include "CollisionSystem.h"
#include <shared_mutex>
#include "CollisionConstants.h"
#include "EntityColAABB.h"
#include "GetEntityColAABB.h"
#include "ColIdMake.h"
#include "spatialhash/SpatialHashClear.h"
#include "spatialhash/SpatialHashInsert.h"
#include "spatialhash/SpatialHashQuery.h"

void collisionSystem(Context &ctx)
{
    auto &cr = ctx.collision.collisions;
    cr.count = 0;

    auto &npc = ctx.data.npc;
    auto &object = ctx.data.object;
    auto &player = ctx.data.player;

    SDL_FRect pBox = entityColAABB(player.base, 0);
    auto &hash = ctx.collision.spatialHash;
    {
        std::unique_lock lock(ctx.collision.spatialHashMutex);
        spatialHashClear(hash);

        spatialHashInsert(hash, pBox, colIdMake(ColType::Player, 0));

        for (uint32_t i = 0; i < npc.npcCount; i++)
            spatialHashInsert(hash, entityColAABB(npc.base, i), colIdMake(ColType::NPC, i));

        for (uint32_t i = 0; i < object.objectCount; i++)
            spatialHashInsert(hash, entityColAABB(object.base, i), colIdMake(ColType::Object, i));
    }

    std::shared_lock readLock(ctx.collision.spatialHashMutex);
    uint32_t candidates[SpatialHash::MAX_PER_BUCKET * 4];

    auto addPair = [&](uint32_t a, uint32_t b)
    {
        if (cr.count < MAX_COLLISION_PAIRS)
        {
            cr.pair.a[cr.count] = a;
            cr.pair.b[cr.count] = b;
            cr.count++;
        }
    };

    // For each entity, query candidates with higher ID to avoid duplicate pairs
    auto checkEntity = [&](uint32_t id, SDL_FRect colBox)
    {
        int n = spatialHashQuery(hash, colBox, candidates, SpatialHash::MAX_PER_BUCKET * 4);
        for (int k = 0; k < n; k++)
        {
            uint32_t other = candidates[k];
            if (other <= id)
                continue;
            SDL_FRect ob = getEntityColAABB(ctx, other);
            if (SDL_HasRectIntersectionFloat(&colBox, &ob))
                addPair(id, other);
        }
    };

    checkEntity(colIdMake(ColType::Player, 0), pBox);
    for (uint32_t i = 0; i < npc.npcCount; i++)
        checkEntity(colIdMake(ColType::NPC, i), entityColAABB(npc.base, i));
    for (uint32_t i = 0; i < object.objectCount; i++)
        checkEntity(colIdMake(ColType::Object, i), entityColAABB(object.base, i));
}
