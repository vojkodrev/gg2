#include "SerpentStingDebuffSystem.h"
#include "ApplyAttackDamage.h"
#include "debuff/RemoveDebuff.h"
#include "../../../structs/core/constants/SerpentStingConstants.h"
#include <algorithm>

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

        auto &debuff = npc.serpentStingDebuff;
        for (uint32_t j = 0; j < debuff.pool.count[i]; j++)
        {
            if (!debuff.pool.active[i][j])
                continue;

            const float prevTimer = debuff.timer[i][j];
            const float nextTimer = std::max(0.0f, prevTimer - dt);
            debuff.timer[i][j] = nextTimer;

            const int prevTicks =
                (int)((SERPENT_STING_DEBUFF_TIME - prevTimer) / tickTime);
            const int nextTicks =
                (int)((SERPENT_STING_DEBUFF_TIME - nextTimer) / tickTime);
            const int tickCount = std::max(0, nextTicks - prevTicks);
            if (tickCount > 0)
                applyAttackDamage(
                    ctx,
                    EntityType::NPC,
                    i,
                    npc.statistics,
                    npc.group,
                    npc.base,
                    SERPENT_STING_DAMAGE * tickCount,
                    0);

            if (nextTimer <= 0.0f)
                removeDebuff(debuff, i, (int)j);
        }
    }
}
