#include "ScaleNpcSizeSystem.h"
#include "ScaleEntityBaseSizes.h"
#include <cstdint>

void scaleNpcSizeSystem(Context &ctx)
{
    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
        scaleEntityBaseSizes(ctx.data.npc.base, i);
}
