#pragma once
#include <cmath>

inline float dist(float ax, float ay, float bx, float by)
{
    const float dx = ax - bx;
    const float dy = ay - by;
    return sqrtf(dx * dx + dy * dy);
}
