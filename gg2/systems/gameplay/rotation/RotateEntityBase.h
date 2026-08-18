#pragma once
#include "IsRotationAnimationRunning.h"
#include "../../../structs/entity/EntityBase.h"
#include "../../../utils/collision/EntityColCenter.h"
#include "../../../utils/rect/RotateRectCenter.h"
#include <cstdint>

template<int N>
inline void rotateEntityBase(
    EntityBase<N> &entityBase,
    uint32_t entityIndex,
    bool useRotationAnimationStart = false)
{
    if (entityBase.animation.frameCount[entityIndex] == 0)
        return;

    const bool useAnimatedRotation =
        isRotationAnimationRunning(entityBase, entityIndex);
    if (useAnimatedRotation)
    {
        entityBase.rotation.rotate[entityIndex] =
            entityBase.animation.rotate[entityIndex];
    }
    else if (useRotationAnimationStart)
    {
        entityBase.rotation.rotate[entityIndex] =
            entityBase.facing.flipX[entityIndex]
            ? 360.0f -
                entityBase.animation.rotationStartAngle[entityIndex] +
                entityBase.rotation.initialAngle[entityIndex]
            : entityBase.animation.rotationStartAngle[entityIndex] -
                entityBase.rotation.initialAngle[entityIndex];
    }
    else
    {
        entityBase.rotation.rotate[entityIndex] =
            entityBase.facing.flipX[entityIndex]
            ? -entityBase.rotation.initialRotate[entityIndex]
            : entityBase.rotation.initialRotate[entityIndex];
    }

    if (useAnimatedRotation || useRotationAnimationStart)
    {
        const int frameIndex = entityBase.animation.frameIndex[entityIndex];
        const SDL_FPoint center =
            entityColCenter(
                entityBase.animation.frame.anchor,
                entityIndex,
                frameIndex);
        entityBase.rotation.center.point.x[entityIndex][0] = center.x;
        entityBase.rotation.center.point.y[entityIndex][0] = center.y;
        entityBase.rotation.center.exists[entityIndex] = true;
    }
    else
    {
        entityBase.rotation.center.exists[entityIndex] = false;
    }

    const float entityCenterX = entityBase.position.w[entityIndex] * 0.5f;
    const float entityCenterY = entityBase.position.h[entityIndex] * 0.5f;
    for (int frameIndex = 0;
        frameIndex < entityBase.animation.frameCount[entityIndex];
        frameIndex++)
    {
        const SDL_FPoint center = (useAnimatedRotation || useRotationAnimationStart)
            ? entityColCenter(
                entityBase.animation.frame.anchor,
                entityIndex,
                frameIndex)
            : SDL_FPoint{entityCenterX, entityCenterY};
        if (!(useAnimatedRotation || useRotationAnimationStart))
            rotateRectCenter(
                entityBase.animation.frame.anchor.offX[entityIndex][frameIndex][0],
                entityBase.animation.frame.anchor.offY[entityIndex][frameIndex][0],
                entityBase.animation.frame.anchor.w[entityIndex][frameIndex][0],
                entityBase.animation.frame.anchor.h[entityIndex][frameIndex][0],
                center.x,
                center.y,
                entityBase.rotation.rotate[entityIndex]);
        for (int collisionIndex = 0;
            collisionIndex < MAX_FRAME_COLLISIONS;
            collisionIndex++)
            if (entityBase.animation.frame.collision
                    .exists[entityIndex][frameIndex][collisionIndex])
                rotateRectCenter(
                    entityBase.animation.frame.collision
                        .offX[entityIndex][frameIndex][collisionIndex],
                    entityBase.animation.frame.collision
                        .offY[entityIndex][frameIndex][collisionIndex],
                    entityBase.animation.frame.collision
                        .w[entityIndex][frameIndex][collisionIndex],
                    entityBase.animation.frame.collision
                        .h[entityIndex][frameIndex][collisionIndex],
                    center.x,
                    center.y,
                    entityBase.rotation.rotate[entityIndex]);
    }
}
