#pragma once
#include <SDL3/SDL.h>
#include "Context.h"
#include "Player.h"
#include "NPC.h"
#include "Object.h"

inline SDL_FRect entityAABB(const Player &p)
{
    return {p.x + p.colOffX, p.y + p.colOffY, p.colW, p.colH};
}

inline SDL_FRect entityAABB(const NPC &npc, uint32_t i)
{
    return {
        npc.position.x[i] + npc.collision.offX[i],
        npc.position.y[i] + npc.collision.offY[i],
        npc.collision.w[i],
        npc.collision.h[i]};
}

inline SDL_FRect entityAABB(const Object &object, uint32_t i)
{
    return {
        object.position.x[i] + object.collision.offX[i],
        object.position.y[i] + object.collision.offY[i],
        object.collision.w[i],
        object.collision.h[i]};
}

inline SDL_FRect getEntityAABB(Context &ctx, uint16_t id)
{
    if (id == COLLISION_ENTITY_PLAYER)
        return entityAABB(ctx.data.player);
    if (id <= MAX_NPCS)
        return entityAABB(ctx.data.npc, id - 1);
    return entityAABB(ctx.data.object, id - 1 - MAX_NPCS);
}
