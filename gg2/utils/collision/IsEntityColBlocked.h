#pragma once
#include "EntityColAABB.h"
#include <SDL3/SDL.h>
#include <cstdint>

template<int NEntities>
inline bool isEntityColBlocked(
    const EntityBase<NEntities> &base,
    uint32_t entityIndex,
    const SDL_FRect &moverBox)
{
    if (base.animation.frameCount[entityIndex] == 0)
        return false;

    const int frameIndex = base.animation.frameIndex[entityIndex];
    for (int collisionIndex = 0;
        collisionIndex < MAX_FRAME_COLLISIONS;
        collisionIndex++)
    {
        if (!base.animation.frame.collision
                .exists[entityIndex][frameIndex][collisionIndex])
            continue;

        const SDL_FRect obstacle = entityColAABB(
            base,
            entityIndex,
            collisionIndex);
        if (SDL_HasRectIntersectionFloat(&moverBox, &obstacle))
            return true;
    }

    return false;
}
