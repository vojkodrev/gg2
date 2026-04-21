#include "CollisionSystem.h"

static bool aabbOverlap(float ax, float ay, float aw, float ah,
                        float bx, float by, float bw, float bh)
{
    return ax < bx + bw && ax + aw > bx &&
           ay < by + bh && ay + ah > by;
}

struct AABB
{
    float x, y, w, h;
};

static AABB playerAABB(const Player &p)
{
    return {p.x + p.colOffX, p.y + p.colOffY, p.colW, p.colH};
}

static AABB npcAABB(const NPC &npc, uint32_t i)
{
    return {
        npc.position.x[i] + npc.collision.offX[i],
        npc.position.y[i] + npc.collision.offY[i],
        npc.collision.w[i],
        npc.collision.h[i]};
}

static AABB objectAABB(const Object &object, uint32_t i)
{
    return {
        object.position.x[i] + object.collision.offX[i],
        object.position.y[i] + object.collision.offY[i],
        object.collision.w[i],
        object.collision.h[i]};
}

void CollisionSystem(Context &ctx)
{
    auto &cr = ctx.collisions;
    cr.count = 0;

    auto &npc = ctx.data.npc;
    auto &object = ctx.data.object;
    auto &player = ctx.data.player;

    auto &hash = ctx.spatialHash;
    hash.clear();

    AABB pBox = playerAABB(player);
    hash.insert(pBox.x, pBox.y, pBox.w, pBox.h, COLLISION_ENTITY_PLAYER);

    for (uint32_t i = 0; i < npc.npcCount; i++)
    {
        AABB box = npcAABB(npc, i);
        hash.insert(box.x, box.y, box.w, box.h, (uint16_t)(1 + i));
    }

    for (uint32_t i = 0; i < object.objectCount; i++)
    {
        AABB box = objectAABB(object, i);
        hash.insert(box.x, box.y, box.w, box.h, (uint16_t)(1 + MAX_NPCS + i));
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

    auto getAABB = [&](uint16_t id) -> AABB
    {
        if (id == COLLISION_ENTITY_PLAYER)
            return pBox;
        if (id <= MAX_NPCS)
            return npcAABB(npc, id - 1);
        return objectAABB(object, id - 1 - MAX_NPCS);
    };

    // For each entity, query candidates with higher ID to avoid duplicate pairs
    auto checkEntity = [&](uint16_t id, AABB box)
    {
        int n = hash.query(box.x, box.y, box.w, box.h, candidates,
                           SpatialHash::MAX_PER_BUCKET * 4);
        for (int k = 0; k < n; k++)
        {
            uint16_t other = candidates[k];
            if (other <= id)
                continue;
            AABB ob = getAABB(other);
            if (aabbOverlap(box.x, box.y, box.w, box.h, ob.x, ob.y, ob.w, ob.h))
                addPair(id, other);
        }
    };

    checkEntity(COLLISION_ENTITY_PLAYER, pBox);
    for (uint32_t i = 0; i < npc.npcCount; i++)
        checkEntity((uint16_t)(1 + i), npcAABB(npc, i));
    for (uint32_t i = 0; i < object.objectCount; i++)
        checkEntity((uint16_t)(1 + MAX_NPCS + i), objectAABB(object, i));
}
