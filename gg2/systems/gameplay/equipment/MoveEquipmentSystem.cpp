#include "MoveEquipmentSystem.h"
#include "AlignAmmoToWeaponAnchor.h"
#include "../rotation/IsRotationAnimationRunning.h"
#include "../../../utils/rect/AlignEntityToParentAnchor.h"

void moveEquipmentSystem(Context &ctx)
{
    const bool playerWeaponRotationRunning =
        isRotationAnimationRunning(ctx.data.player.equipment.weapon.base, 0);
    if (
        ctx.data.player.base.position.dirty[0] ||
        ctx.data.player.base.facing.dirty[0] ||
        playerWeaponRotationRunning)
    {
        alignEntityToParentAnchor(
            ctx.data.player.equipment.weapon.base,
            ctx.data.player.base.animation,
            ctx.data.player.base.position,
            0);
        alignAmmoToWeaponAnchor(
            ctx.data.player.equipment.ammo.base,
            ctx.data.player.equipment.weapon.ammoAnchor,
            ctx.data.player.equipment.weapon.base,
            ctx.data.player.base,
            0);
    }

    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!ctx.data.npc.active[i])
            continue;

        const bool npcWeaponRotationRunning =
            isRotationAnimationRunning(ctx.data.npc.equipment.weapon.base, i);
        if (
            !ctx.data.npc.base.position.dirty[i] &&
            !ctx.data.npc.base.facing.dirty[i] &&
            !npcWeaponRotationRunning)
            continue;

        alignEntityToParentAnchor(
            ctx.data.npc.equipment.weapon.base,
            ctx.data.npc.base.animation,
            ctx.data.npc.base.position,
            i);
        alignAmmoToWeaponAnchor(
            ctx.data.npc.equipment.ammo.base,
            ctx.data.npc.equipment.weapon.ammoAnchor,
            ctx.data.npc.equipment.weapon.base,
            ctx.data.npc.base,
            i);
    }
}
