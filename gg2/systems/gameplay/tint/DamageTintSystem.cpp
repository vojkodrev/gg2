#include "DamageTintSystem.h"
#include "TintWhenHpDrops.h"
#include <cstdint>

void damageTintSystem(Context &ctx)
{
    tintWhenHpDrops(ctx.data.player.base, ctx.data.player.statistics, 1);
    tintWhenHpDrops(ctx.data.npc.base, ctx.data.npc.statistics, ctx.data.npc.npcCount);
}
