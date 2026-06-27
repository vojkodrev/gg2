#include "CalculateTintSystem.h"
#include "CalculateEntityBaseTint.h"
#include <cstdint>

void calculateTintSystem(Context &ctx)
{
    const float dt = ctx.frame.dt;

    calculateEntityBaseTint(ctx.data.player.base, 0, dt);
    calculateEntityBaseTint(ctx.data.player.equipment.weapon.base, 0, dt);
    calculateEntityBaseTint(ctx.data.player.equipment.ammo.base, 0, dt);

    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!ctx.data.npc.active[i])
            continue;

        calculateEntityBaseTint(ctx.data.npc.base, i, dt);
        calculateEntityBaseTint(ctx.data.npc.equipment.weapon.base, i, dt);
        calculateEntityBaseTint(ctx.data.npc.equipment.ammo.base, i, dt);
    }
}
