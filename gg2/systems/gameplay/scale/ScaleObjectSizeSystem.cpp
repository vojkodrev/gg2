#include "ScaleObjectSizeSystem.h"
#include "ScaleEntityBaseSizes.h"
#include <cstdint>

void scaleObjectSizeSystem(Context &ctx)
{
    for (uint32_t i = 0; i < ctx.data.object.objectCount; i++)
        scaleEntityBaseSizes(ctx.data.object.base, i);
}
