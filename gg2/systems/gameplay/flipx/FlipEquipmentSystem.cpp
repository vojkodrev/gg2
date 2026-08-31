#include "FlipEquipmentSystem.h"
#include "MirrorEquipmentAnchorsAndCollisionOffsets.h"
#include "../rotation/ShouldClearRotationAnimationStart.h"
#include "../rotation/IsRotationAnimationFinished.h"
#include "../rotation/IsRotationAnimationRunning.h"
#include "../rotation/ShouldUseRotationAnimationStart.h"
#include <cstdint>

void flipEquipmentSystem(Context &ctx)
{
    auto &playerEquipment = ctx.data.player.equipment;
    auto &playerWeapon = playerEquipment.weapon;
    const bool playerWeaponNeedsMirror =
        playerWeapon.exists[0] &&
        (playerWeapon.base.facing.dirty[0] ||
         isRotationAnimationRunning(playerWeapon.base, 0) ||
         isRotationAnimationFinished(playerWeapon.base, 0));
    const bool playerAmmoNeedsMirror =
        playerEquipment.ammo.exists[0] &&
        playerEquipment.ammo.base.facing.dirty[0];
    mirrorEquipmentAnchorsAndCollisionOffsets(
        playerEquipment,
        0,
        playerWeaponNeedsMirror && playerWeapon.base.facing.flipX[0],
        playerAmmoNeedsMirror);

    for (uint32_t entityIndex = 0; entityIndex < MAX_NPCS; entityIndex++)
    {
        if (!ctx.data.npc.active[entityIndex])
            continue;

        auto &npcEquipment = ctx.data.npc.equipment;
        auto &npcWeapon = npcEquipment.weapon;
        const bool npcWeaponNeedsMirror =
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
        const bool npcAmmoNeedsMirror =
            npcEquipment.ammo.exists[entityIndex] &&
            npcEquipment.ammo.base.facing.dirty[entityIndex];
        mirrorEquipmentAnchorsAndCollisionOffsets(
            npcEquipment,
            entityIndex,
            npcWeaponNeedsMirror &&
                npcWeapon.base.facing.flipX[entityIndex],
            npcAmmoNeedsMirror);
    }
}
