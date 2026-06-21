#include "DamageTintSystem.h"
#include "ApplyDamageTint.h"
#include <cstdint>

void damageTintSystem(Context &ctx)
{
    applyDamageTint(ctx.data.player.base, ctx.data.player.statistics, 1);
    applyDamageTint(ctx.data.player.equipment.weapon.base, ctx.data.player.statistics, 1);
    applyDamageTint(ctx.data.player.equipment.ammo.base, ctx.data.player.statistics, 1);

    applyDamageTint(ctx.data.npc.base, ctx.data.npc.statistics, ctx.data.npc.npcCount);
    applyDamageTint(ctx.data.npc.equipment.weapon.base, ctx.data.npc.statistics, ctx.data.npc.npcCount);
    applyDamageTint(ctx.data.npc.equipment.ammo.base, ctx.data.npc.statistics, ctx.data.npc.npcCount);
}
