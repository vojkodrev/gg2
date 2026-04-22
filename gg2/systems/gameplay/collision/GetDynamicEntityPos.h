#pragma once
#include "Context.h"

inline void GetDynamicEntityPos(Context &ctx, uint16_t id, float *&ox, float *&oy)
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
