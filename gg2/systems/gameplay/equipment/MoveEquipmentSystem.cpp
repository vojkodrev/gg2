#include "MoveEquipmentSystem.h"
#include "AlignAmmoToWeaponAnchor.h"
#include "../rotation/IsRotationAnimationRunning.h"
#include "../rotation/ShouldUseRotationAnimationStart.h"
#include "../../../utils/rect/AlignEntityToParentAnchor.h"

void moveEquipmentSystem(Context &ctx)
{
    auto &playerEquipment = ctx.data.player.equipment;
    if (
        playerEquipment.weapon.exists[0] &&
        (ctx.data.player.base.position.dirty[0] ||
         ctx.data.player.base.facing.dirty[0] ||
         isRotationAnimationRunning(playerEquipment.weapon.base, 0)))
    {
        alignEntityToParentAnchor(
            playerEquipment.weapon.base,
            ctx.data.player.base.animation,
            ctx.data.player.base.position,
            0);
        if (playerEquipment.ammo.exists[0])
            alignAmmoToWeaponAnchor(
                playerEquipment.ammo.base,
                playerEquipment.weapon.ranged.ammoAnchor,
                playerEquipment.weapon.base,
                ctx.data.player.base,
                0);
    }

    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        auto &npcEquipment = ctx.data.npc.equipment;
        if (!ctx.data.npc.active[i] ||
            !npcEquipment.weapon.exists[i])
            continue;

        if (
            !ctx.data.npc.base.position.dirty[i] &&
            !ctx.data.npc.base.facing.dirty[i] &&
            !isRotationAnimationRunning(npcEquipment.weapon.base, i) &&
            !shouldUseRotationAnimationStart(
                ctx.data.npc.ai,
                npcEquipment.weapon,
                i))
            continue;

        alignEntityToParentAnchor(
            npcEquipment.weapon.base,
            ctx.data.npc.base.animation,
            ctx.data.npc.base.position,
            i);
        if (npcEquipment.ammo.exists[i])
            alignAmmoToWeaponAnchor(
                npcEquipment.ammo.base,
                npcEquipment.weapon.ranged.ammoAnchor,
                npcEquipment.weapon.base,
                ctx.data.npc.base,
                i);
    }
}
