#pragma once
#include <cstdint>
#include "RenderSrc.h"
#include "RenderDst.h"
#include "RenderGroup.h"
#include "../core/Facing.h"
#include "CapacityConstants.h"

struct RenderBuffer
{
    uint32_t count;
    uint32_t groupCount;
    
    RenderSrc src;
    RenderDst dst;
    
    RenderGroup group;
    
    bool flipX[MAX_RENDER_BUFFER];
};
