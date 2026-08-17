#pragma once
#include "ColIdIndex.h"
#include "ColIdType.h"
#include "IsEntityColBlocked.h"
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
    for (int candidateIndex = 0;
        candidateIndex < candidateCount;
        candidateIndex++)
    {
        const uint32_t id = candidates[candidateIndex];
        const ColType type = colIdType(id);
        const uint32_t entityIndex = colIdIndex(id);

        if (type == ColType::Object)
        {
            if (isEntityColBlocked(
                    ctx.data.object.base,
                    entityIndex,
                    moverBox))
                return true;
        }
        else if (type == ColType::NPC &&
            static_cast<int>(entityIndex) != npcIndex &&
            static_cast<int>(entityIndex) != targetNpcIndex)
        {
            if (isEntityColBlocked(
                    ctx.data.npc.base,
                    entityIndex,
                    moverBox))
                return true;
        }
        else if (type == ColType::Player && isPlayerBlocking)
        {
            if (isEntityColBlocked(
                    ctx.data.player.base,
                    0,
                    moverBox))
                return true;
        }
    }

    return false;
}
