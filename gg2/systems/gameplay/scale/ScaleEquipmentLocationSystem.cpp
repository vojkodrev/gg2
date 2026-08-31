#include "ScaleEquipmentLocationSystem.h"
#include "../rotation/ShouldClearRotationAnimationStart.h"
#include "../rotation/IsRotationAnimationFinished.h"
#include "../rotation/IsRotationAnimationRunning.h"
#include "../rotation/ShouldUseRotationAnimationStart.h"
#include "ScaleEquipmentLocations.h"

void scaleEquipmentLocationSystem(Context &ctx)
{
    auto &playerEquipment = ctx.data.player.equipment;
    auto &playerWeapon = playerEquipment.weapon;
    const bool playerWeaponNeedsReset =
        playerWeapon.exists[0] &&
        (playerWeapon.base.facing.dirty[0] ||
         isRotationAnimationRunning(playerWeapon.base, 0) ||
         isRotationAnimationFinished(playerWeapon.base, 0));
    const bool playerAmmoNeedsReset =
        playerEquipment.ammo.exists[0] &&
        playerEquipment.ammo.base.facing.dirty[0];
    scaleEquipmentLocations(
        playerEquipment,
        0,
        playerWeaponNeedsReset,
        playerAmmoNeedsReset);

    for (uint32_t entityIndex = 0; entityIndex < MAX_NPCS; entityIndex++)
    {
        if (!ctx.data.npc.active[entityIndex])
            continue;

        auto &npcEquipment = ctx.data.npc.equipment;
        auto &npcWeapon = npcEquipment.weapon;
        const bool npcWeaponNeedsReset =
            npcWeapon.exists[entityIndex] &&
            (npcWeapon.base.facing.dirty[entityIndex] ||
             isRotationAnimationRunning(npcWeapon.base, entityIndex) ||
             isRotationAnimationFinished(npcWeapon.base, entityIndex) ||
             shouldUseRotationAnimationStart(
                ctx.data.npc.ai,
                npcWeapon,
                entityIndex) ||
             shouldClearRotationAnimationStart(
                ctx.data.npc.ai,
                npcWeapon,
                entityIndex));
        const bool npcAmmoNeedsReset =
            npcEquipment.ammo.exists[entityIndex] &&
            npcEquipment.ammo.base.facing.dirty[entityIndex];
        scaleEquipmentLocations(
            npcEquipment,
            entityIndex,
            npcWeaponNeedsReset,
            npcAmmoNeedsReset);
    }
}
