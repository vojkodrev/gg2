#include "ShowHealthbarSystem.h"
#include <cstdint>

void showHealthbarSystem(Context &ctx)
{
    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
        ctx.data.npc.healthbar.show[i] =
            ctx.data.npc.statistics.hp[i] < ctx.data.npc.statistics.maxHp[i];
}
