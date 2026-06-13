#pragma once
#include "Context.h"
#include "ColIdIndex.h"
#include "ColIdType.h"

inline SDL_FPoint getDynamicEntityPos(Context &ctx, uint32_t id)
{
    if (colIdType(id) == ColType::Player)
        return {ctx.data.player.base.position.x[0], ctx.data.player.base.position.y[0]};
    uint32_t i = colIdIndex(id);
    return {ctx.data.npc.base.position.x[i], ctx.data.npc.base.position.y[i]};
}
