#pragma once
#include <SDL3/SDL.h>
#include "Context.h"
#include "ColId.h"
#include "EntityColAABB.h"

inline SDL_FRect getEntityColAABB(Context &ctx, uint16_t id)
{
    if (colIdIsPlayer(id))
        return entityColAABB(ctx.data.player.base, 0);
    if (colIdIsNpc(id))
        return entityColAABB(ctx.data.npc.base, colIdNpcIndex(id));
    return entityColAABB(ctx.data.object.base, colIdObjectIndex(id));
}
