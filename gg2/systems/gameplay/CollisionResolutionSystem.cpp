#include "CollisionResolutionSystem.h"
#include <cmath>

// Entity ID: 0 = player, 1+i = NPC i
static const uint16_t PLAYER_ID = 0;

struct Box { float x, y, w, h; };

static Box playerBox(const Player &p)
{
    return { p.x + p.colOffX, p.y + p.colOffY, p.colW, p.colH };
}

static Box npcBox(const NPC &npc, uint32_t i)
{
    return {
        npc.position.x[i] + npc.collision.offX[i],
        npc.position.y[i] + npc.collision.offY[i],
        npc.collision.w[i],
        npc.collision.h[i]
    };
}

static void getPos(Context &ctx, uint16_t id, float *&ox, float *&oy)
{
    if (id == PLAYER_ID) {
        ox = &ctx.data.player.x;
        oy = &ctx.data.player.y;
    } else {
        uint32_t i = id - 1;
        ox = &ctx.data.npc.position.x[i];
        oy = &ctx.data.npc.position.y[i];
    }
}

static Box getBox(Context &ctx, uint16_t id)
{
    if (id == PLAYER_ID) return playerBox(ctx.data.player);
    return npcBox(ctx.data.npc, id - 1);
}

void CollisionResolutionSystem(Context &ctx)
{
    auto &cr = ctx.collisions;

    for (uint32_t k = 0; k < cr.count; k++)
    {
        uint16_t idA = cr.pair.a[k];
        uint16_t idB = cr.pair.b[k];

        Box a = getBox(ctx, idA);
        Box b = getBox(ctx, idB);

        float overlapX = std::fminf(a.x + a.w, b.x + b.w) - std::fmaxf(a.x, b.x);
        float overlapY = std::fminf(a.y + a.h, b.y + b.h) - std::fmaxf(a.y, b.y);

        if (overlapX <= 0.0f || overlapY <= 0.0f) continue;

        float *axPtr, *ayPtr, *bxPtr, *byPtr;
        getPos(ctx, idA, axPtr, ayPtr);
        getPos(ctx, idB, bxPtr, byPtr);

        // Push along the axis of least overlap, split equally
        if (overlapX < overlapY)
        {
            float push = overlapX * 0.5f;
            if (a.x < b.x) { *axPtr -= push; *bxPtr += push; }
            else            { *axPtr += push; *bxPtr -= push; }
        }
        else
        {
            float push = overlapY * 0.5f;
            if (a.y < b.y) { *ayPtr -= push; *byPtr += push; }
            else            { *ayPtr += push; *byPtr -= push; }
        }
    }
}
