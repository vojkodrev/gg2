#include "ScaleNpcLocationSystem.h"
#include "ScaleEntityBaseLocations.h"
#include <cstdint>

void scaleNpcLocationSystem(Context &ctx)
{
    for (uint32_t i = 0; i < ctx.data.npc.pool.count; i++)
    {
        if (!ctx.data.npc.pool.active[i])
            continue;

        if (!ctx.data.npc.base.facing.dirty[i])
            continue;

        scaleEntityBaseLocations(ctx.data.npc.base, i);
    }
}
