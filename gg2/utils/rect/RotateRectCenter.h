#pragma once
#include <cmath>

inline void rotateRectCenter(float &offX, float &offY, float w, float h, float pivotX, float pivotY, float angle)
{
    if (angle == 0.0f)
        return;

    const float radians = angle * 3.14159265358979323846f / 180.0f;
    const float sinAngle = sinf(radians);
    const float cosAngle = cosf(radians);
    const float centerX = offX + w * 0.5f;
    const float centerY = offY + h * 0.5f;
    const float dx = centerX - pivotX;
    const float dy = centerY - pivotY;
    const float rotatedCenterX = pivotX + dx * cosAngle - dy * sinAngle;
    const float rotatedCenterY = pivotY + dx * sinAngle + dy * cosAngle;
    offX = rotatedCenterX - w * 0.5f;
    offY = rotatedCenterY - h * 0.5f;
}
