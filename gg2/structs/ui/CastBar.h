#pragma once
#include "CastType.h"
#include "ProgressBar.h"

template<int N>
struct CastBar
{
    ProgressBar<N> progressBar;
    CastType type[N] = {};
    float timer[N] = {};
    float duration[N] = {};
    float hideTimer[N] = {};
};
