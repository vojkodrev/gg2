#include "ClearTintSystem.h"
#include "ClearTintWhenTimerExpires.h"
#include <cstdint>

void clearTintSystem(Context &ctx)
{
    const float dt = ctx.frame.dt;

    clearTintWhenTimerExpires(ctx.data.player.base, 1, dt);
    clearTintWhenTimerExpires(ctx.data.player.equipment.weapon.base, 1, dt);
    clearTintWhenTimerExpires(ctx.data.player.equipment.ammo.base, 1, dt);

    clearTintWhenTimerExpires(ctx.data.npc.base, ctx.data.npc.npcCount, dt);
    clearTintWhenTimerExpires(ctx.data.npc.equipment.weapon.base, ctx.data.npc.npcCount, dt);
    clearTintWhenTimerExpires(ctx.data.npc.equipment.ammo.base, ctx.data.npc.npcCount, dt);
}
