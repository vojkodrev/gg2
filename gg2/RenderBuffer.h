#pragma once
#include <cstdint>
#include "RenderSrc.h"
#include "RenderDst.h"

struct RenderBuffer
{
    uint32_t count;
    RenderSrc src;
    RenderDst dst;
};
