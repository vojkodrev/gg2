#include "SerpentStingDebuffSystem.h"
#include "../statistics/SetHpDamage.h"
#include "../effects/CreateEntityTextEffect.h"
#include "../../../structs/core/constants/SerpentStingConstants.h"
#include <algorithm>
#include <string>

void serpentStingDebuffSystem(Context &ctx)
{
    const float dt = ctx.frame.dt;
    auto &npc = ctx.data.npc;
    const float tickTime =
        SERPENT_STING_DEBUFF_TIME / (float)SERPENT_STING_TICK_COUNT;

    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!npc.active[i])
            continue;

        const float prevTimer = npc.serpentStingDebuffTimer[i];
        if (prevTimer <= 0.0f)
            continue;

        const float nextTimer = std::max(0.0f, prevTimer - dt);
        npc.serpentStingDebuffTimer[i] = nextTimer;

        const int prevTicks =
            (int)((SERPENT_STING_DEBUFF_TIME - prevTimer) / tickTime);
        const int nextTicks =
            (int)((SERPENT_STING_DEBUFF_TIME - nextTimer) / tickTime);
        const int tickCount = std::max(0, nextTicks - prevTicks);
        if (tickCount == 0)
            continue;

        const int damage = SERPENT_STING_DAMAGE * tickCount;
        const int appliedDamage = setHpDamage(npc.statistics, i, damage);
        if (appliedDamage > 0)
            createEntityTextEffect(
                ctx,
                npc.group.id[i],
                EntityType::NPC,
                i,
                npc.base,
                std::to_string(appliedDamage));
    }
}
