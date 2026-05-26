#pragma once
#include <SDL3/SDL.h>
#include "Context.h"
#include "ColId.h"
#include "EntityBaseColAABB.h"

inline SDL_FRect getEntityColAABB(Context &ctx, uint16_t id)
{
    if (colIdIsPlayer(id))
        return entityBaseColAABB(ctx.data.player.base, 0);
    if (colIdIsNpc(id))
        return entityBaseColAABB(ctx.data.npc.base, colIdNpcIndex(id));
    return entityBaseColAABB(ctx.data.object.base, colIdObjectIndex(id));
}
