#include "ScaleNpcSystem.h"
#include "ScaleEntityBase.h"
#include <cstdint>

void scaleNpcSystem(Context &ctx)
{
    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
        scaleEntityBase(ctx.data.npc.base, i);
}
