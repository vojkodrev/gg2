#pragma once
#include "Context.h"

inline SDL_FPoint getDynamicEntityPos(Context &ctx, uint16_t id)
{
    if (id == COLLISION_ENTITY_PLAYER)
        return {ctx.data.player.base.position.x[0], ctx.data.player.base.position.y[0]};
    uint32_t i = id - 1;
    return {ctx.data.npc.base.position.x[i], ctx.data.npc.base.position.y[i]};
}
