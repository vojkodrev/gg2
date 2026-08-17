#pragma once
#include "../../structs/entity/EntityBase.h"
#include "../../structs/core/constants/AnimationConstants.h"

template<int TFromCount, int TToCount>
inline void copyEntityBaseSlot(
    const EntityBase<TFromCount> &from,
    int fromIndex,
    EntityBase<TToCount> &to,
    int toIndex)
{
    to.animation.animationType[toIndex] = from.animation.animationType[fromIndex];
    to.animation.animationState[toIndex] = from.animation.animationState[fromIndex];
    to.animation.animationStop[toIndex] = from.animation.animationStop[fromIndex];
    to.animation.frameCount[toIndex] = from.animation.frameCount[fromIndex];
    to.animation.frameIndex[toIndex] = from.animation.frameIndex[fromIndex];
    to.animation.cycleDuration[toIndex] = from.animation.cycleDuration[fromIndex];
    to.animation.animationStartTime[toIndex] = from.animation.animationStartTime[fromIndex];
    to.animation.rotate[toIndex] = from.animation.rotate[fromIndex];
    to.animation.rotationStartAngle[toIndex] = from.animation.rotationStartAngle[fromIndex];
    to.animation.rotationStopAngle[toIndex] = from.animation.rotationStopAngle[fromIndex];

    for (int frameIndex = 0;
        frameIndex < MAX_ANIMATION_FRAMES;
        frameIndex++)
    {
        to.animation.frame.src.x[toIndex][frameIndex] =
            from.animation.frame.src.x[fromIndex][frameIndex];
        to.animation.frame.src.y[toIndex][frameIndex] =
            from.animation.frame.src.y[fromIndex][frameIndex];
        to.animation.frame.src.w[toIndex][frameIndex] =
            from.animation.frame.src.w[fromIndex][frameIndex];
        to.animation.frame.src.h[toIndex][frameIndex] =
            from.animation.frame.src.h[fromIndex][frameIndex];

        to.animation.frame.anchor.exists[toIndex][frameIndex][0] =
            from.animation.frame.anchor.exists[fromIndex][frameIndex][0];
        to.animation.frame.anchor.initialOffX[toIndex][frameIndex][0] =
            from.animation.frame.anchor.initialOffX[fromIndex][frameIndex][0];
        to.animation.frame.anchor.initialOffY[toIndex][frameIndex][0] =
            from.animation.frame.anchor.initialOffY[fromIndex][frameIndex][0];
        to.animation.frame.anchor.initialW[toIndex][frameIndex][0] =
            from.animation.frame.anchor.initialW[fromIndex][frameIndex][0];
        to.animation.frame.anchor.initialH[toIndex][frameIndex][0] =
            from.animation.frame.anchor.initialH[fromIndex][frameIndex][0];
        to.animation.frame.anchor.offX[toIndex][frameIndex][0] =
            from.animation.frame.anchor.offX[fromIndex][frameIndex][0];
        to.animation.frame.anchor.offY[toIndex][frameIndex][0] =
            from.animation.frame.anchor.offY[fromIndex][frameIndex][0];
        to.animation.frame.anchor.w[toIndex][frameIndex][0] =
            from.animation.frame.anchor.w[fromIndex][frameIndex][0];
        to.animation.frame.anchor.h[toIndex][frameIndex][0] =
            from.animation.frame.anchor.h[fromIndex][frameIndex][0];

        for (int collisionIndex = 0;
            collisionIndex < MAX_FRAME_COLLISIONS;
            collisionIndex++)
        {
            to.animation.frame.collision
                .exists[toIndex][frameIndex][collisionIndex] =
                from.animation.frame.collision
                    .exists[fromIndex][frameIndex][collisionIndex];
            if (!from.animation.frame.collision
                    .exists[fromIndex][frameIndex][collisionIndex])
                continue;
            to.animation.frame.collision
                .initialOffX[toIndex][frameIndex][collisionIndex] =
                from.animation.frame.collision
                    .initialOffX[fromIndex][frameIndex][collisionIndex];
            to.animation.frame.collision
                .initialOffY[toIndex][frameIndex][collisionIndex] =
                from.animation.frame.collision
                    .initialOffY[fromIndex][frameIndex][collisionIndex];
            to.animation.frame.collision
                .initialW[toIndex][frameIndex][collisionIndex] =
                from.animation.frame.collision
                    .initialW[fromIndex][frameIndex][collisionIndex];
            to.animation.frame.collision
                .initialH[toIndex][frameIndex][collisionIndex] =
                from.animation.frame.collision
                    .initialH[fromIndex][frameIndex][collisionIndex];
            to.animation.frame.collision
                .offX[toIndex][frameIndex][collisionIndex] =
                from.animation.frame.collision
                    .offX[fromIndex][frameIndex][collisionIndex];
            to.animation.frame.collision
                .offY[toIndex][frameIndex][collisionIndex] =
                from.animation.frame.collision
                    .offY[fromIndex][frameIndex][collisionIndex];
            to.animation.frame.collision
                .w[toIndex][frameIndex][collisionIndex] =
                from.animation.frame.collision
                    .w[fromIndex][frameIndex][collisionIndex];
            to.animation.frame.collision
                .h[toIndex][frameIndex][collisionIndex] =
                from.animation.frame.collision
                    .h[fromIndex][frameIndex][collisionIndex];
        }

        to.animation.frame.frameDuration[toIndex][frameIndex] =
            from.animation.frame.frameDuration[fromIndex][frameIndex];
    }

    to.position.x[toIndex] = from.position.x[fromIndex];
    to.position.y[toIndex] = from.position.y[fromIndex];
    to.position.initialW[toIndex] = from.position.initialW[fromIndex];
    to.position.initialH[toIndex] = from.position.initialH[fromIndex];
    to.position.w[toIndex] = from.position.w[fromIndex];
    to.position.h[toIndex] = from.position.h[fromIndex];
    to.position.absolute[toIndex] = from.position.absolute[fromIndex];
    to.position.dirty[toIndex] = from.position.dirty[fromIndex];

    to.depthY[toIndex] = from.depthY[fromIndex];

    to.scale.value[toIndex] = from.scale.value[fromIndex];

    to.rotation.initialAngle[toIndex] = from.rotation.initialAngle[fromIndex];
    to.rotation.rotate[toIndex] = from.rotation.rotate[fromIndex];
    to.rotation.initialRotate[toIndex] = from.rotation.initialRotate[fromIndex];
    to.rotation.center.point.x[toIndex][0] = from.rotation.center.point.x[fromIndex][0];
    to.rotation.center.point.y[toIndex][0] = from.rotation.center.point.y[fromIndex][0];
    to.rotation.center.exists[toIndex] = from.rotation.center.exists[fromIndex];

    to.facing.facing[toIndex] = from.facing.facing[fromIndex];
    to.facing.initialFacing[toIndex] = from.facing.initialFacing[fromIndex];
    to.facing.dirty[toIndex] = from.facing.dirty[fromIndex];
    to.facing.flipX[toIndex] = from.facing.flipX[fromIndex];

    to.tint.r[toIndex] = from.tint.r[fromIndex];
    to.tint.g[toIndex] = from.tint.g[fromIndex];
    to.tint.b[toIndex] = from.tint.b[fromIndex];
    to.tint.a[toIndex] = from.tint.a[fromIndex];
    to.tint.damageTimer[toIndex] = from.tint.damageTimer[fromIndex];
    to.tint.isPoisoned[toIndex] = from.tint.isPoisoned[fromIndex];
}
