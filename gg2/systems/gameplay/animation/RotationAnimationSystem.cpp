#include "RotationAnimationSystem.h"
#include "AnimateWeaponRotation.h"

void rotationAnimationSystem(Context &ctx)
{
    auto &playerWeapon = ctx.data.player.equipment.weapon;
    if (playerWeapon.exists[0])
        animateWeaponRotation(playerWeapon.base, 0, ctx.frame.now);

    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!ctx.data.npc.active[i] ||
            !ctx.data.npc.equipment.weapon.exists[i])
            continue;

        animateWeaponRotation(ctx.data.npc.equipment.weapon.base, i, ctx.frame.now);
    }
}
