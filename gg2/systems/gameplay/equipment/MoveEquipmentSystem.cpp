#include "MoveEquipmentSystem.h"
#include "AlignAmmoToWeaponAnchor.h"
#include "../rotation/IsRotationAnimationRunning.h"
#include "../rotation/ShouldUseRotationAnimationStart.h"
#include "../../../utils/rect/AlignEntityToParentAnchor.h"

void moveEquipmentSystem(Context &ctx)
{
    if (
        ctx.data.player.base.position.dirty[0] ||
        ctx.data.player.base.facing.dirty[0] ||
        isRotationAnimationRunning(ctx.data.player.equipment.weapon.base, 0))
    {
        alignEntityToParentAnchor(
            ctx.data.player.equipment.weapon.base,
            ctx.data.player.base.animation,
            ctx.data.player.base.position,
            0);
        alignAmmoToWeaponAnchor(
            ctx.data.player.equipment.ammo.base,
            ctx.data.player.equipment.weapon.ranged.ammoAnchor,
            ctx.data.player.equipment.weapon.base,
            ctx.data.player.base,
            0);
    }

    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!ctx.data.npc.active[i])
            continue;

        if (
            !ctx.data.npc.base.position.dirty[i] &&
            !ctx.data.npc.base.facing.dirty[i] &&
            !isRotationAnimationRunning(ctx.data.npc.equipment.weapon.base, i) &&
            !shouldUseRotationAnimationStart(
                ctx.data.npc.ai,
                ctx.data.npc.equipment.weapon,
                i))
            continue;

        alignEntityToParentAnchor(
            ctx.data.npc.equipment.weapon.base,
            ctx.data.npc.base.animation,
            ctx.data.npc.base.position,
            i);
        alignAmmoToWeaponAnchor(
            ctx.data.npc.equipment.ammo.base,
            ctx.data.npc.equipment.weapon.ranged.ammoAnchor,
            ctx.data.npc.equipment.weapon.base,
            ctx.data.npc.base,
            i);
    }
}
