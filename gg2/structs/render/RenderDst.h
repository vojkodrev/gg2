#pragma once
#include "RenderBufferConstants.h"

struct RenderDst
{
    float x[MAX_RENDER_BUFFER];
    float y[MAX_RENDER_BUFFER];
    float w[MAX_RENDER_BUFFER];
    float h[MAX_RENDER_BUFFER];
    float depthY[MAX_RENDER_BUFFER];
    bool absolute[MAX_RENDER_BUFFER];
};
