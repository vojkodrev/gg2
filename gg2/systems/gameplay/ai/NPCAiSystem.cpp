#include "NPCAiSystem.h"
#include "monster/UpdateMonster.h"
#include "pet/UpdatePet.h"

void npcAiSystem(Context &ctx)
{
    auto &npc = ctx.data.npc;

    for (uint32_t n = 0; n < npc.npcCount; n++)
    {
        if (npc.ai.type[n] == NPCAiType::Monster)
            updateMonster(n, ctx);
        else if (npc.ai.type[n] == NPCAiType::Pet)
            updatePet(n, ctx);
    }
}
