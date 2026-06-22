#include "NPCAiSystem.h"
#include "monster/RunMonsterAi.h"
#include "pet/RunPetAi.h"

void npcAiSystem(Context &ctx)
{
    auto &npc = ctx.data.npc;

    for (uint32_t n = 0; n < npc.pool.count; n++)
    {
        if (!npc.pool.active[n])
            continue;

        if (npc.ai.type[n] == NPCAiType::Monster)
            runMonsterAi(n, ctx);
        else if (npc.ai.type[n] == NPCAiType::Pet)
            runPetAi(n, ctx);
    }
}
