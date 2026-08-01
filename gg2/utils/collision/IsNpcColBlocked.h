#pragma once
#include "ColIdIndex.h"
#include "ColIdType.h"
#include "EntityColAABB.h"
#include "../../structs/core/Context.h"
#include <cstdint>

inline bool isNpcColBlocked(
    const Context &ctx,
    const SDL_FRect &moverBox,
    const uint32_t *candidates,
    int candidateCount,
    int npcIndex,
    int targetNpcIndex,
    bool isPlayerBlocking)
{
    for (int i = 0; i < candidateCount; i++)
    {
        const uint32_t id = candidates[i];
        const ColType type = colIdType(id);
        SDL_FRect obstacle;

        if (type == ColType::Object)
            obstacle = entityColAABB(
                ctx.data.object.base,
                colIdIndex(id));
        else if (type == ColType::NPC &&
            (int)colIdIndex(id) != npcIndex &&
            (int)colIdIndex(id) != targetNpcIndex)
            obstacle = entityColAABB(
                ctx.data.npc.base,
                colIdIndex(id));
        else if (type == ColType::Player && isPlayerBlocking)
            obstacle = entityColAABB(ctx.data.player.base, 0);
        else
            continue;

        if (SDL_HasRectIntersectionFloat(&moverBox, &obstacle))
            return true;
    }

    return false;
}
