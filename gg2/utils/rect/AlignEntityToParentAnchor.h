#pragma once
#include <cstdint>
#include "../../../utils/animation/AnchorOrCollision.h"
#include "../../../structs/core/EntityBase.h"
#include "../../../utils/collision/EntityColCenter.h"

template<int N>
inline void alignEntityToParentAnchor(
    EntityBase<N> &entityBase,
    const Animation<N> &parentAnimation,
    const EntityPosition<N> &parentPosition,
    uint32_t i)
{
    int pf = parentAnimation.frameIndex[i];
    SDL_FRect parentAnchor = anchorOrCollision(parentAnimation, i, pf);
    alignEntityToParentAnchor(entityBase, parentAnchor, parentPosition, i);
}

template<int N>
inline void alignEntityToParentAnchor(
    EntityBase<N> &entityBase,
    SDL_FRect &parentAnchor,
    const EntityPosition<N> &parentPosition,
    uint32_t i)
{
    auto &animation = entityBase.animation;
    if (animation.frameCount[i] == 0)
        return;

    int ef = animation.frameIndex[i];

    SDL_FRect entityAnchor = anchorOrCollision(animation, i, ef);

    SDL_FRect parentAnchorWorld = {
        parentPosition.x[i] + parentAnchor.x,
        parentPosition.y[i] + parentAnchor.y,
        parentAnchor.w,
        parentAnchor.h};
    SDL_FPoint parentAnchorCenterWorld = entityColCenter(parentAnchorWorld);

    SDL_FPoint entityAnchorCenterLocal = entityColCenter(entityAnchor);

    entityBase.position.x[i] = parentAnchorCenterWorld.x - entityAnchorCenterLocal.x;
    entityBase.position.y[i] = parentAnchorCenterWorld.y - entityAnchorCenterLocal.y;
}
