#pragma once
#include "CapacityConstants.h"

struct RenderDst
{
    float x[MAX_RENDER_BUFFER];
    float y[MAX_RENDER_BUFFER];
    float w[MAX_RENDER_BUFFER];
    float h[MAX_RENDER_BUFFER];
    float sortY[MAX_RENDER_BUFFER];
};
