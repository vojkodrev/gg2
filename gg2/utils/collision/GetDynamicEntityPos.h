#pragma once
#include "Context.h"

inline SDL_FPoint getDynamicEntityPos(Context &ctx, uint16_t id)
{
    if (id == COLLISION_ENTITY_PLAYER)
        return {ctx.data.player.x, ctx.data.player.y};
    uint32_t i = id - 1;
    return {ctx.data.npc.position.x[i], ctx.data.npc.position.y[i]};
}
