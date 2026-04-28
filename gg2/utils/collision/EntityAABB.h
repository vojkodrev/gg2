#pragma once
#include <SDL3/SDL.h>
#include "Context.h"
#include "Player.h"
#include "NPC.h"
#include "Object.h"
#include "ColId.h"

inline SDL_FRect entityColAABB(const Player &p, float buffer = 0.0f)
{
    return {p.x + p.colOffX - buffer, p.y + p.colOffY - buffer,
            p.colW + buffer * 2, p.colH + buffer * 2};
}

inline SDL_FRect entityColAABB(const NPC &npc, uint32_t i, float buffer = 0.0f)
{
    return {
        npc.position.x[i] + npc.collision.offX[i] - buffer,
        npc.position.y[i] + npc.collision.offY[i] - buffer,
        npc.collision.w[i] + buffer * 2,
        npc.collision.h[i] + buffer * 2};
}

inline SDL_FRect entityColAABB(const Object &object, uint32_t i, float buffer = 0.0f)
{
    return {
        object.position.x[i] + object.collision.offX[i] - buffer,
        object.position.y[i] + object.collision.offY[i] - buffer,
        object.collision.w[i] + buffer * 2,
        object.collision.h[i] + buffer * 2};
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
