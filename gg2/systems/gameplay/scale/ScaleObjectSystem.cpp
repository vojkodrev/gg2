#include "ScaleObjectSystem.h"
#include "ScaleEntityBase.h"
#include <cstdint>

void scaleObjectSystem(Context &ctx)
{
    for (uint32_t i = 0; i < ctx.data.object.objectCount; i++)
        scaleEntityBase(ctx.data.object.base, i);
}
