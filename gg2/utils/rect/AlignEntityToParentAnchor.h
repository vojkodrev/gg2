#pragma once
#include <cstdint>
#include "../../../utils/animation/AnchorOrCollision.h"
#include "../../../utils/collision/EntityColCenter.h"
#include "AlignEntityToAnchorCenter.h"

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
    const SDL_FRect &parentAnchor,
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
    const SDL_FPoint parentAnchorCenterWorld = entityColCenter(parentAnchorWorld);
    alignEntityToAnchorCenter(entityBase, entityAnchor, parentAnchorCenterWorld, i);
}
