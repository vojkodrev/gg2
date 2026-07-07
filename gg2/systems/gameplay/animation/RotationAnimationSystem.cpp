#include "RotationAnimationSystem.h"
#include "AnimateWeaponRotation.h"

void rotationAnimationSystem(Context &ctx)
{
    animateWeaponRotation(ctx.data.player.equipment.weapon.base, 0, ctx.frame.now);

    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!ctx.data.npc.active[i])
            continue;

        animateWeaponRotation(ctx.data.npc.equipment.weapon.base, i, ctx.frame.now);
    }
}
