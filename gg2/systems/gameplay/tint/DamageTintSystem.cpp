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

        const bool isPoisoned = ctx.data.npc.serpentStingDebuffTimer[i] > 0.0f;
        const bool isSlowed = ctx.data.npc.concussiveShotDebuffTimer[i] > 0.0f;
        applyDamageTint(ctx.data.npc.base, ctx.data.npc.statistics, i);
        applyDamageTint(ctx.data.npc.equipment.weapon.base, ctx.data.npc.statistics, i);
        applyDamageTint(ctx.data.npc.equipment.ammo.base, ctx.data.npc.statistics, i);
        ctx.data.npc.base.tint.isPoisoned[i] = isPoisoned;
        ctx.data.npc.equipment.weapon.base.tint.isPoisoned[i] = isPoisoned;
        ctx.data.npc.equipment.ammo.base.tint.isPoisoned[i] = isPoisoned;
        ctx.data.npc.base.tint.isSlowed[i] = isSlowed;
        ctx.data.npc.equipment.weapon.base.tint.isSlowed[i] = isSlowed;
        ctx.data.npc.equipment.ammo.base.tint.isSlowed[i] = isSlowed;
    }
}
