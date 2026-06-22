#include "NpcDepthSystem.h"
#include "SetEntityBaseDepthY.h"
#include <cstdint>

void npcDepthSystem(Context &ctx)
{
    for (uint32_t i = 0; i < ctx.data.npc.pool.count; i++)
    {
        if (!ctx.data.npc.pool.active[i])
            continue;

        setEntityBaseDepthY(ctx.data.npc.base, i);
    }
}
