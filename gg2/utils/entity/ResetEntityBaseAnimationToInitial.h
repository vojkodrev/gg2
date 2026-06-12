#pragma once
#include "../../structs/core/EntityBase.h"
#include "../../structs/core/constants/AnimationConstants.h"

template<int N>
inline void resetEntityBaseAnimationToInitial(EntityBase<N> &entityBase, int index)
{
    for (int f = 0; f < MAX_ANIMATION_FRAMES; f++)
    {
        entityBase.animation.frame.anchor.offX[index][f] = entityBase.animation.frame.anchor.initialOffX[index][f];
        entityBase.animation.frame.anchor.offY[index][f] = entityBase.animation.frame.anchor.initialOffY[index][f];
        entityBase.animation.frame.anchor.w[index][f] = entityBase.animation.frame.anchor.initialW[index][f];
        entityBase.animation.frame.anchor.h[index][f] = entityBase.animation.frame.anchor.initialH[index][f];

        entityBase.animation.frame.collision.offX[index][f] = entityBase.animation.frame.collision.initialOffX[index][f];
        entityBase.animation.frame.collision.offY[index][f] = entityBase.animation.frame.collision.initialOffY[index][f];
        entityBase.animation.frame.collision.w[index][f] = entityBase.animation.frame.collision.initialW[index][f];
        entityBase.animation.frame.collision.h[index][f] = entityBase.animation.frame.collision.initialH[index][f];
    }
}
