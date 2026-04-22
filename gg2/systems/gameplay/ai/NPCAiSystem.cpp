#include "NPCAiSystem.h"
#include "UpdateMonster.h"

void NPCAiSystem(Context &ctx)
{
    auto &npc = ctx.data.npc;

    for (uint32_t n = 0; n < npc.npcCount; n++)
    {
        if (npc.ai.type[n] == NPCAiType::Monster)
            updateMonster(n, ctx);
    }
}
