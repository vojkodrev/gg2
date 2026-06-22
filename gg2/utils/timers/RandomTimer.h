#pragma once
#include <cstdlib>

inline float randomTimer(float minValue, float maxValue)
{
    return minValue + (float)rand() / (float)RAND_MAX * (maxValue - minValue);
}
