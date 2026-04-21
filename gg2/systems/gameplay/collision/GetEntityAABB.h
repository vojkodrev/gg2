#pragma once
#include "EntityAABB.h"
#include "Context.h"

inline SDL_FRect getEntityAABB(Context &ctx, uint16_t id)
{
    if (id == COLLISION_ENTITY_PLAYER)
        return entityAABB(ctx.data.player);
    if (id <= MAX_NPCS)
        return entityAABB(ctx.data.npc, id - 1);
    return entityAABB(ctx.data.object, id - 1 - MAX_NPCS);
}
