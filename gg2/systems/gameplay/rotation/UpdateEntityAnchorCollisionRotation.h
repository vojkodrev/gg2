#pragma once
#include "../../../structs/core/Animation.h"
#include "../../../utils/rect/RotateRectCenter.h"
#include <cstdint>

template<int N>
inline void updateEntityAnchorCollisionRotation(Animation<N> &animation, uint32_t i, float entityW, float entityH, float angle)
{
    if (angle == 0.0f)
        return;

    const float entityCenterX = entityW * 0.5f;
    const float entityCenterY = entityH * 0.5f;

    for (int f = 0; f < animation.frameCount[i]; f++)
    {
        rotateRectCenter(
            animation.frame.anchor.offX[i][f],
            animation.frame.anchor.offY[i][f],
            animation.frame.anchor.w[i][f],
            animation.frame.anchor.h[i][f],
            entityCenterX,
            entityCenterY,
            angle);
        rotateRectCenter(
            animation.frame.collision.offX[i][f],
            animation.frame.collision.offY[i][f],
            animation.frame.collision.w[i][f],
            animation.frame.collision.h[i][f],
            entityCenterX,
            entityCenterY,
            angle);
    }
}
