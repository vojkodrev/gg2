#pragma once
#include "Context.h"
#include "ColIdIndex.h"
#include "ColIdType.h"

inline void setDynamicEntityPos(Context &ctx, uint32_t id, SDL_FPoint pos)
{
    if (colIdType(id) == ColType::Player)
    {
        ctx.data.player.base.position.dirty[0] =
            ctx.data.player.base.position.dirty[0] ||
            ctx.data.player.base.position.x[0] != pos.x ||
            ctx.data.player.base.position.y[0] != pos.y;
        ctx.data.player.base.position.x[0] = pos.x;
        ctx.data.player.base.position.y[0] = pos.y;
    }
    else
    {
        uint32_t i = colIdIndex(id);
        ctx.data.npc.base.position.dirty[i] =
            ctx.data.npc.base.position.dirty[i] ||
            ctx.data.npc.base.position.x[i] != pos.x ||
            ctx.data.npc.base.position.y[i] != pos.y;
        ctx.data.npc.base.position.x[i] = pos.x;
        ctx.data.npc.base.position.y[i] = pos.y;
    }
}
