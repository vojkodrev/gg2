#pragma once
#include <cstdint>
#include "RenderSrc.h"
#include "RenderDst.h"
#include "../core/Facing.h"
#include "CapacityConstants.h"

struct RenderBuffer
{
    uint32_t count;
    RenderSrc src;
    RenderDst dst;
    bool flipX[MAX_RENDER_BUFFER];
};
