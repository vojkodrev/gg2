#include "ScaleNpcLocationSystem.h"
#include "ScaleEntityBaseLocations.h"
#include <cstdint>

void scaleNpcLocationSystem(Context &ctx)
{
    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
        scaleEntityBaseLocations(ctx.data.npc.base, i);
}
