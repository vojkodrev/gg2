#pragma once
#include "../../../structs/core/Animation.h"
#include <cmath>
#include <cstdint>

template<int N>
inline void updateEntityAnchorAndCollisionRotation(Animation<N> &animation, uint32_t i, float entityW, float entityH, float angle)
{
    if (angle == 0.0f)
        return;

    const float radians = angle * 3.14159265358979323846f / 180.0f;
    const float sinAngle = sinf(radians);
    const float cosAngle = cosf(radians);
    const float entityCenterX = entityW * 0.5f;
    const float entityCenterY = entityH * 0.5f;

    for (int f = 0; f < animation.frameCount[i]; f++)
    {
        auto rotateRectCenter = [&](float &offX, float &offY, float w, float h)
        {
            const float centerX = offX + w * 0.5f;
            const float centerY = offY + h * 0.5f;
            const float dx = centerX - entityCenterX;
            const float dy = centerY - entityCenterY;
            const float rotatedCenterX = entityCenterX + dx * cosAngle - dy * sinAngle;
            const float rotatedCenterY = entityCenterY + dx * sinAngle + dy * cosAngle;
            offX = rotatedCenterX - w * 0.5f;
            offY = rotatedCenterY - h * 0.5f;
        };

        rotateRectCenter(
            animation.frame.anchor.offX[i][f],
            animation.frame.anchor.offY[i][f],
            animation.frame.anchor.w[i][f],
            animation.frame.anchor.h[i][f]);
        rotateRectCenter(
            animation.frame.collision.offX[i][f],
            animation.frame.collision.offY[i][f],
            animation.frame.collision.w[i][f],
            animation.frame.collision.h[i][f]);
    }
}
