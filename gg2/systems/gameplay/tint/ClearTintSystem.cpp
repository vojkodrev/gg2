#include "ClearTintSystem.h"
#include "ClearTintWhenTimerExpires.h"
#include <cstdint>

void clearTintSystem(Context &ctx)
{
    const float dt = ctx.frame.dt;

    clearTintWhenTimerExpires(ctx.data.player.base, 0, dt);
    clearTintWhenTimerExpires(ctx.data.player.equipment.weapon.base, 0, dt);
    clearTintWhenTimerExpires(ctx.data.player.equipment.ammo.base, 0, dt);

    for (uint32_t i = 0; i < ctx.data.npc.pool.count; i++)
    {
        if (!ctx.data.npc.pool.active[i])
            continue;

        clearTintWhenTimerExpires(ctx.data.npc.base, i, dt);
        clearTintWhenTimerExpires(ctx.data.npc.equipment.weapon.base, i, dt);
        clearTintWhenTimerExpires(ctx.data.npc.equipment.ammo.base, i, dt);
    }
}
