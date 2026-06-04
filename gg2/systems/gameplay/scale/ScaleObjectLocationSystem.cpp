#include "ScaleObjectLocationSystem.h"
#include "ScaleEntityBaseLocations.h"
#include <cstdint>

void scaleObjectLocationSystem(Context &ctx)
{
    for (uint32_t i = 0; i < ctx.data.object.objectCount; i++)
        scaleEntityBaseLocations(ctx.data.object.base, i);
}
