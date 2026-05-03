#pragma once
#include "Context.h"

inline void setDynamicEntityPos(Context &ctx, uint16_t id, SDL_FPoint pos)
{
    if (id == COLLISION_ENTITY_PLAYER)
    {
        ctx.data.player.position.x[0] = pos.x;
        ctx.data.player.position.y[0] = pos.y;
    }
    else
    {
        uint32_t i = id - 1;
        ctx.data.npc.position.x[i] = pos.x;
        ctx.data.npc.position.y[i] = pos.y;
    }
}
