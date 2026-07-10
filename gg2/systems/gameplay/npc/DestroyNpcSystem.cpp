#include "DestroyNpcSystem.h"
#include "../../../structs/core/constants/IndexConstants.h"
#include "../../../structs/core/constants/NpcConstants.h"
#include "../../../structs/core/EntityType.h"
#include "../../../structs/effect/EffectType.h"
#include "../effects/EffectFree.h"
#include "select/SetSelectedNpc.h"

void destroyNpcSystem(Context &ctx)
{
    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!ctx.data.npc.active[i])
            continue;

        if (ctx.data.npc.statistics.health.hp[i] > 0)
            continue;

        if (ctx.data.player.selectedNpc == static_cast<int>(i))
            setSelectedNpc(ctx, INVALID_ID);

        for (uint32_t effectIndex = 0; effectIndex < ctx.data.effect.pool.count; effectIndex++)
        {
            if (!ctx.data.effect.pool.active[effectIndex])
                continue;

            if (ctx.data.effect.type[effectIndex] != EffectType::Projectile)
                continue;

            if (ctx.data.effect.target.type[effectIndex] != EntityType::NPC)
                continue;

            if (ctx.data.effect.target.id[effectIndex] != static_cast<int>(i))
                continue;

            effectFree(ctx.data.effect, ctx.data.groups, effectIndex);
        }

        ctx.data.npc.active[i] = false;
        ctx.data.npc.inactiveTimer[i] = NPC_INACTIVE_TIME;
    }
}
