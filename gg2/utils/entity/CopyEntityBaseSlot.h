#pragma once
#include "../../structs/core/EntityBase.h"
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

    for (int f = 0; f < MAX_ANIMATION_FRAMES; f++)
    {
        to.animation.frame.src.x[toIndex][f] = from.animation.frame.src.x[fromIndex][f];
        to.animation.frame.src.y[toIndex][f] = from.animation.frame.src.y[fromIndex][f];
        to.animation.frame.src.w[toIndex][f] = from.animation.frame.src.w[fromIndex][f];
        to.animation.frame.src.h[toIndex][f] = from.animation.frame.src.h[fromIndex][f];

        to.animation.frame.anchor.initialOffX[toIndex][f] = from.animation.frame.anchor.initialOffX[fromIndex][f];
        to.animation.frame.anchor.initialOffY[toIndex][f] = from.animation.frame.anchor.initialOffY[fromIndex][f];
        to.animation.frame.anchor.initialW[toIndex][f] = from.animation.frame.anchor.initialW[fromIndex][f];
        to.animation.frame.anchor.initialH[toIndex][f] = from.animation.frame.anchor.initialH[fromIndex][f];
        to.animation.frame.anchor.offX[toIndex][f] = from.animation.frame.anchor.offX[fromIndex][f];
        to.animation.frame.anchor.offY[toIndex][f] = from.animation.frame.anchor.offY[fromIndex][f];
        to.animation.frame.anchor.w[toIndex][f] = from.animation.frame.anchor.w[fromIndex][f];
        to.animation.frame.anchor.h[toIndex][f] = from.animation.frame.anchor.h[fromIndex][f];

        to.animation.frame.collision.initialOffX[toIndex][f] = from.animation.frame.collision.initialOffX[fromIndex][f];
        to.animation.frame.collision.initialOffY[toIndex][f] = from.animation.frame.collision.initialOffY[fromIndex][f];
        to.animation.frame.collision.initialW[toIndex][f] = from.animation.frame.collision.initialW[fromIndex][f];
        to.animation.frame.collision.initialH[toIndex][f] = from.animation.frame.collision.initialH[fromIndex][f];
        to.animation.frame.collision.offX[toIndex][f] = from.animation.frame.collision.offX[fromIndex][f];
        to.animation.frame.collision.offY[toIndex][f] = from.animation.frame.collision.offY[fromIndex][f];
        to.animation.frame.collision.w[toIndex][f] = from.animation.frame.collision.w[fromIndex][f];
        to.animation.frame.collision.h[toIndex][f] = from.animation.frame.collision.h[fromIndex][f];

        to.animation.frame.frameDuration[toIndex][f] = from.animation.frame.frameDuration[fromIndex][f];
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
    to.rotation.center.point.x[toIndex] = from.rotation.center.point.x[fromIndex];
    to.rotation.center.point.y[toIndex] = from.rotation.center.point.y[fromIndex];
    to.rotation.center.hasCenter[toIndex] = from.rotation.center.hasCenter[fromIndex];

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
