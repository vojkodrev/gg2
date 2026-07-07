#pragma once
#include <SDL3/SDL.h>
#include "Context.h"
#include "ColIdIndex.h"
#include "ColIdType.h"
#include "EntityColAABB.h"
#include "../../structs/core/EntityType.h"

inline SDL_FRect getEntityColAABB(Context &ctx, uint32_t id)
{
    const ColType type = colIdType(id);

    if (type == ColType::Player)
        return entityColAABB(ctx.data.player.base, 0);
    if (type == ColType::NPC)
        return entityColAABB(ctx.data.npc.base, colIdIndex(id));
    if (type == ColType::Object)
        return entityColAABB(ctx.data.object.base, colIdIndex(id));
    return entityColAABB(ctx.data.effect.base, colIdIndex(id));
}

inline SDL_FRect getEntityColAABB(Context &ctx, EntityType type, int id)
{
    if (type == EntityType::Player)
        return entityColAABB(ctx.data.player.base, static_cast<uint32_t>(id));
    if (type == EntityType::NPC)
        return entityColAABB(ctx.data.npc.base, static_cast<uint32_t>(id));
    return {};
}
