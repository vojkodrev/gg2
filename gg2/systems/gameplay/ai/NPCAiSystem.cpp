#include "NPCAiSystem.h"
#include "friendly/FriendlyAi.h"
#include "monster/MonsterMeleeAi.h"
#include "pet/PetAi.h"

void npcAiSystem(Context &ctx)
{
    auto &npc = ctx.data.npc;

    for (uint32_t n = 0; n < MAX_NPCS; n++)
    {
        if (!npc.active[n])
            continue;

        if (npc.ai.type[n] == NPCAiType::MonsterMelee)
            monsterMeleeAi(n, ctx);
        else if (npc.ai.type[n] == NPCAiType::Friendly)
            friendlyAi(n, ctx);
        else if (npc.ai.type[n] == NPCAiType::Pet)
            petAi(n, ctx);
    }
}
