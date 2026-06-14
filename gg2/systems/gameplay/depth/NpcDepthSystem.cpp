#include "NpcDepthSystem.h"
#include "SetEntityBaseDepthY.h"
#include <cstdint>

void npcDepthSystem(Context &ctx)
{
    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
        setEntityBaseDepthY(ctx.data.npc.base, i);
}
