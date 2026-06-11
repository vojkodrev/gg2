#pragma once
#include <SDL3/SDL.h>
#include <cstdint>
#include "RenderSrc.h"
#include "RenderDst.h"
#include "RenderGroup.h"
#include "../core/RotationCenter.h"
#include "../core/Facing.h"
#include "RenderConstants.h"

struct RenderBuffer
{
    uint32_t count;
    
    RenderSrc src;
    RenderDst dst;
    RotationCenter<MAX_RENDER_BUFFER> rotationCenter;
    
    RenderGroup group;
    
    bool flipX[MAX_RENDER_BUFFER];
};
