#pragma once
#include "../../structs/entity/EntityBase.h"
#include "../../structs/core/constants/AnimationConstants.h"

template<int N>
inline void resetEntityBaseAnimationToInitial(EntityBase<N> &entityBase, int index)
{
    for (int frameIndex = 0;
        frameIndex < MAX_ANIMATION_FRAMES;
        frameIndex++)
    {
        entityBase.animation.frame.anchor.offX[index][frameIndex][0] =
            entityBase.animation.frame.anchor.initialOffX[index][frameIndex][0];
        entityBase.animation.frame.anchor.offY[index][frameIndex][0] =
            entityBase.animation.frame.anchor.initialOffY[index][frameIndex][0];
        entityBase.animation.frame.anchor.w[index][frameIndex][0] =
            entityBase.animation.frame.anchor.initialW[index][frameIndex][0];
        entityBase.animation.frame.anchor.h[index][frameIndex][0] =
            entityBase.animation.frame.anchor.initialH[index][frameIndex][0];

        for (int collisionIndex = 0;
            collisionIndex < MAX_FRAME_COLLISIONS;
            collisionIndex++)
        {
            if (!entityBase.animation.frame.collision
                    .exists[index][frameIndex][collisionIndex])
                continue;
            entityBase.animation.frame.collision
                .offX[index][frameIndex][collisionIndex] =
                entityBase.animation.frame.collision
                    .initialOffX[index][frameIndex][collisionIndex];
            entityBase.animation.frame.collision
                .offY[index][frameIndex][collisionIndex] =
                entityBase.animation.frame.collision
                    .initialOffY[index][frameIndex][collisionIndex];
            entityBase.animation.frame.collision
                .w[index][frameIndex][collisionIndex] =
                entityBase.animation.frame.collision
                    .initialW[index][frameIndex][collisionIndex];
            entityBase.animation.frame.collision
                .h[index][frameIndex][collisionIndex] =
                entityBase.animation.frame.collision
                    .initialH[index][frameIndex][collisionIndex];
        }
    }
}
