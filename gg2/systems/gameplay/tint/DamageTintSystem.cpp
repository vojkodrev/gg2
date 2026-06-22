#include "DamageTintSystem.h"
#include "ApplyDamageTint.h"
#include <cstdint>

void damageTintSystem(Context &ctx)
{
    applyDamageTint(ctx.data.player.base, ctx.data.player.statistics, 0);
    applyDamageTint(ctx.data.player.equipment.weapon.base, ctx.data.player.statistics, 0);
    applyDamageTint(ctx.data.player.equipment.ammo.base, ctx.data.player.statistics, 0);

    for (uint32_t i = 0; i < ctx.data.npc.pool.count; i++)
    {
        if (!ctx.data.npc.pool.active[i])
            continue;

        applyDamageTint(ctx.data.npc.base, ctx.data.npc.statistics, i);
        applyDamageTint(ctx.data.npc.equipment.weapon.base, ctx.data.npc.statistics, i);
        applyDamageTint(ctx.data.npc.equipment.ammo.base, ctx.data.npc.statistics, i);
    }
}
