#pragma once
#include "ProgressBar.h"

template<int N>
struct CastBar
{
    ProgressBar<N> progressBar;
    float timer[N] = {};
    float duration[N] = {};
};
