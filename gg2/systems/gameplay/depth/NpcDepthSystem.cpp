#include "NpcDepthSystem.h"
#include "SetEntityBaseDepthY.h"
#include <cstdint>

void npcDepthSystem(Context &ctx)
{
    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!ctx.data.npc.active[i])
            continue;

        setEntityBaseDepthY(ctx.data.npc.base, i);
    }
}
