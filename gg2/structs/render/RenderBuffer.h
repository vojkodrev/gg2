#pragma once
#include <cstdint>
#include "RenderSrc.h"
#include "RenderDst.h"
#include "RenderGroup.h"
#include "../core/Facing.h"
#include "RenderConstants.h"

struct RenderBuffer
{
    uint32_t count;
    
    RenderSrc src;
    RenderDst dst;
    
    RenderGroup group;
    
    bool flipX[MAX_RENDER_BUFFER];
};
