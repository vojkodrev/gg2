#pragma once
#include "IsRotationAnimationRunning.h"
#include "../../../structs/core/EntityBase.h"
#include "../../../utils/collision/EntityColCenter.h"
#include "../../../utils/rect/RotateRectCenter.h"
#include <cstdint>

template<int N>
inline void rotateEntityBase(
    EntityBase<N> &entityBase,
    uint32_t i,
    bool useRotationAnimationStart = false)
{
    if (entityBase.animation.frameCount[i] == 0)
        return;

    const bool useAnimatedRotation = isRotationAnimationRunning(entityBase, i);
    if (useAnimatedRotation)
    {
        entityBase.rotation.rotate[i] = entityBase.animation.rotate[i];
    }
    else if (useRotationAnimationStart)
    {
        entityBase.rotation.rotate[i] = entityBase.facing.flipX[i]
            ? 360.0f -
                entityBase.animation.rotationStartAngle[i] +
                entityBase.rotation.initialAngle[i]
            : entityBase.animation.rotationStartAngle[i] -
                entityBase.rotation.initialAngle[i];
    }
    else
    {
        entityBase.rotation.rotate[i] = entityBase.facing.flipX[i]
            ? -entityBase.rotation.initialRotate[i]
            : entityBase.rotation.initialRotate[i];
    }

    if (useAnimatedRotation || useRotationAnimationStart)
    {
        const int frameIndex = entityBase.animation.frameIndex[i];
        const SDL_FPoint center =
            entityColCenter(entityBase.animation.frame.anchor, i, frameIndex);
        entityBase.rotation.center.point.x[i] = center.x;
        entityBase.rotation.center.point.y[i] = center.y;
        entityBase.rotation.center.hasCenter[i] = true;
    }
    else
    {
        entityBase.rotation.center.hasCenter[i] = false;
    }

    const float entityCenterX = entityBase.position.w[i] * 0.5f;
    const float entityCenterY = entityBase.position.h[i] * 0.5f;
    for (int f = 0; f < entityBase.animation.frameCount[i]; f++)
    {
        const SDL_FPoint center = (useAnimatedRotation || useRotationAnimationStart)
            ? entityColCenter(entityBase.animation.frame.anchor, i, f)
            : SDL_FPoint{entityCenterX, entityCenterY};
        if (!(useAnimatedRotation || useRotationAnimationStart))
            rotateRectCenter(
                entityBase.animation.frame.anchor.offX[i][f],
                entityBase.animation.frame.anchor.offY[i][f],
                entityBase.animation.frame.anchor.w[i][f],
                entityBase.animation.frame.anchor.h[i][f],
                center.x,
                center.y,
                entityBase.rotation.rotate[i]);
        rotateRectCenter(
            entityBase.animation.frame.collision.offX[i][f],
            entityBase.animation.frame.collision.offY[i][f],
            entityBase.animation.frame.collision.w[i][f],
            entityBase.animation.frame.collision.h[i][f],
            center.x,
            center.y,
            entityBase.rotation.rotate[i]);
    }
}
