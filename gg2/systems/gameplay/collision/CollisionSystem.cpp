#include "CollisionSystem.h"
#include "EntityAABB.h"
#include "ColId.h"

void collisionSystem(Context &ctx)
{
    auto &cr = ctx.collision.collisions;
    cr.count = 0;

    auto &npc = ctx.data.npc;
    auto &object = ctx.data.object;
    auto &player = ctx.data.player;

    auto &hash = ctx.collision.spatialHash;
    hash.clear();

    SDL_FRect pBox = entityColAABB(player);
    hash.insert(pBox.x, pBox.y, pBox.w, pBox.h, COLLISION_ENTITY_PLAYER);

    for (uint32_t i = 0; i < npc.npcCount; i++)
    {
        SDL_FRect box = entityColAABB(npc, i);
        hash.insert(box.x, box.y, box.w, box.h, colIdNpc(i));
    }

    for (uint32_t i = 0; i < object.objectCount; i++)
    {
        SDL_FRect box = entityColAABB(object, i);
        hash.insert(box.x, box.y, box.w, box.h, colIdObject(i));
    }

    uint16_t candidates[SpatialHash::MAX_PER_BUCKET * 4];

    auto addPair = [&](uint16_t a, uint16_t b)
    {
        if (cr.count < MAX_COLLISION_PAIRS)
        {
            cr.pair.a[cr.count] = a;
            cr.pair.b[cr.count] = b;
            cr.count++;
        }
    };

    // For each entity, query candidates with higher ID to avoid duplicate pairs
    auto checkEntity = [&](uint16_t id, SDL_FRect colBox)
    {
        int n = hash.query(colBox.x, colBox.y, colBox.w, colBox.h, candidates,
                           SpatialHash::MAX_PER_BUCKET * 4);
        for (int k = 0; k < n; k++)
        {
            uint16_t other = candidates[k];
            if (other <= id)
                continue;
            SDL_FRect ob = getEntityColAABB(ctx, other);
            if (SDL_HasRectIntersectionFloat(&colBox, &ob))
                addPair(id, other);
        }
    };

    checkEntity(COLLISION_ENTITY_PLAYER, pBox);
    for (uint32_t i = 0; i < npc.npcCount; i++)
        checkEntity(colIdNpc(i), entityColAABB(npc, i));
    for (uint32_t i = 0; i < object.objectCount; i++)
        checkEntity(colIdObject(i), entityColAABB(object, i));
}
