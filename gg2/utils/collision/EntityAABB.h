#pragma once
#include <SDL3/SDL.h>
#include "Context.h"
#include "Player.h"
#include "NPC.h"
#include "Object.h"
#include "ColId.h"

inline SDL_FRect entityColAABB(const Player &p)
{
    return {p.x + p.colOffX, p.y + p.colOffY, p.colW, p.colH};
}

inline SDL_FRect entityColAABB(const NPC &npc, uint32_t i)
{
    return {
        npc.position.x[i] + npc.collision.offX[i],
        npc.position.y[i] + npc.collision.offY[i],
        npc.collision.w[i],
        npc.collision.h[i]};
}

inline SDL_FRect entityColAABB(const Object &object, uint32_t i)
{
    return {
        object.position.x[i] + object.collision.offX[i],
        object.position.y[i] + object.collision.offY[i],
        object.collision.w[i],
        object.collision.h[i]};
}

inline SDL_FPoint entityColCenter(const SDL_FRect &r)
{
    return {r.x + r.w * 0.5f, r.y + r.h * 0.5f};
}

inline SDL_FRect getEntityColAABB(Context &ctx, uint16_t id)
{
    if (colIdIsPlayer(id))
        return entityColAABB(ctx.data.player);
    if (colIdIsNpc(id))
        return entityColAABB(ctx.data.npc, colIdNpcIndex(id));
    return entityColAABB(ctx.data.object, colIdObjectIndex(id));
}
