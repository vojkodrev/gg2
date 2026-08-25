#pragma once
#include <cstdint>
#include "RenderBufferConstants.h"

struct RenderGroup
{
    uint32_t id[MAX_RENDER_BUFFER];
    int zIndex[MAX_RENDER_BUFFER];
};
