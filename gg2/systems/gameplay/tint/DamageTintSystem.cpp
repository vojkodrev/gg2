#include "DamageTintSystem.h"
#include "ApplyDamageTint.h"
#include <cstdint>

void damageTintSystem(Context &ctx)
{
    applyDamageTint(ctx.data.player.base, ctx.data.player.statistics, 0);
    applyDamageTint(ctx.data.player.equipment.weapon.base, ctx.data.player.statistics, 0);
    applyDamageTint(ctx.data.player.equipment.ammo.base, ctx.data.player.statistics, 0);

    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!ctx.data.npc.active[i])
            continue;

        applyDamageTint(ctx.data.npc.base, ctx.data.npc.statistics, i);
        applyDamageTint(ctx.data.npc.equipment.weapon.base, ctx.data.npc.statistics, i);
        applyDamageTint(ctx.data.npc.equipment.ammo.base, ctx.data.npc.statistics, i);
    }
}
