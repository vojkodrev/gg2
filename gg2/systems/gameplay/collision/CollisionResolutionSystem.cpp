#include "CollisionResolutionSystem.h"
#include "EntityAABB.h"
#include <cmath>

static bool isStatic(uint16_t id) { return id > MAX_NPCS; }

static SDL_FRect getBox(Context &ctx, uint16_t id)
{
    if (id == COLLISION_ENTITY_PLAYER)
        return entityAABB(ctx.data.player);
    if (id <= MAX_NPCS)
        return entityAABB(ctx.data.npc, id - 1);
    return entityAABB(ctx.data.object, id - 1 - MAX_NPCS);
}

static void getPos(Context &ctx, uint16_t id, float *&ox, float *&oy)
{
    if (id == COLLISION_ENTITY_PLAYER)
    {
        ox = &ctx.data.player.x;
        oy = &ctx.data.player.y;
    }
    else
    {
        uint32_t i = id - 1;
        ox = &ctx.data.npc.position.x[i];
        oy = &ctx.data.npc.position.y[i];
    }
}

void CollisionResolutionSystem(Context &ctx)
{
    auto &cr = ctx.collisions;

    for (uint32_t k = 0; k < cr.count; k++)
    {
        uint16_t idA = cr.pair.a[k];
        uint16_t idB = cr.pair.b[k];

        SDL_FRect a = getBox(ctx, idA);
        SDL_FRect b = getBox(ctx, idB);

        float overlapX = std::fminf(a.x + a.w, b.x + b.w) - std::fmaxf(a.x, b.x);
        float overlapY = std::fminf(a.y + a.h, b.y + b.h) - std::fmaxf(a.y, b.y);

        if (overlapX <= 0.0f || overlapY <= 0.0f)
            continue;

        bool staticA = isStatic(idA);
        bool staticB = isStatic(idB);

        float pushA = staticA ? 0.0f : (staticB ? 1.0f : 0.5f);
        float pushB = staticB ? 0.0f : (staticA ? 1.0f : 0.5f);

        float *axPtr, *ayPtr, *bxPtr, *byPtr;
        if (!staticA)
            getPos(ctx, idA, axPtr, ayPtr);
        if (!staticB)
            getPos(ctx, idB, bxPtr, byPtr);

        if (overlapX < overlapY)
        {
            if (a.x < b.x)
            {
                if (!staticA)
                    *axPtr -= overlapX * pushA;
                if (!staticB)
                    *bxPtr += overlapX * pushB;
            }
            else
            {
                if (!staticA)
                    *axPtr += overlapX * pushA;
                if (!staticB)
                    *bxPtr -= overlapX * pushB;
            }
        }
        else
        {
            if (a.y < b.y)
            {
                if (!staticA)
                    *ayPtr -= overlapY * pushA;
                if (!staticB)
                    *byPtr += overlapY * pushB;
            }
            else
            {
                if (!staticA)
                    *ayPtr += overlapY * pushA;
                if (!staticB)
                    *byPtr -= overlapY * pushB;
            }
        }
    }
}
