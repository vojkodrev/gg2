#include "RotateEquipmentSystem.h"
#include "ShouldClearRotationAnimationStart.h"
#include "IsRotationAnimationFinished.h"
#include "IsRotationAnimationRunning.h"
#include "RotateEquipment.h"
#include "ShouldUseRotationAnimationStart.h"
#include <cstdint>

void rotateEquipmentSystem(Context &ctx)
{
    auto &playerEquipment = ctx.data.player.equipment;
    auto &playerWeapon = playerEquipment.weapon;
    const bool rotatePlayerWeapon =
        playerWeapon.exists[0] &&
        (playerWeapon.base.facing.dirty[0] ||
         isRotationAnimationRunning(playerWeapon.base, 0) ||
         isRotationAnimationFinished(playerWeapon.base, 0));
    const bool rotatePlayerAmmo =
        playerEquipment.ammo.exists[0] &&
        playerEquipment.ammo.base.facing.dirty[0] &&
        playerWeapon.type[0] == WeaponType::Ranged;
    rotateEquipment(
        playerEquipment,
        0,
        rotatePlayerWeapon,
        rotatePlayerAmmo);

    auto &npcEquipment = ctx.data.npc.equipment;
    auto &npcWeapon = npcEquipment.weapon;
    for (uint32_t entityIndex = 0; entityIndex < MAX_NPCS; entityIndex++)
    {
        if (!ctx.data.npc.active[entityIndex] ||
            !npcWeapon.exists[entityIndex])
            continue;

        const bool npcWeaponRotationRunning =
            isRotationAnimationRunning(npcWeapon.base, entityIndex);
        const bool npcWeaponRotationFinished =
            isRotationAnimationFinished(npcWeapon.base, entityIndex);
        const bool useRotationAnimationStart =
            shouldUseRotationAnimationStart(
                ctx.data.npc.ai,
                npcWeapon,
                entityIndex);

        const bool rotateNpcWeapon =
            npcWeapon.base.facing.dirty[entityIndex] ||
            npcWeaponRotationRunning ||
            npcWeaponRotationFinished ||
            useRotationAnimationStart ||
            shouldClearRotationAnimationStart(
                ctx.data.npc.ai,
                npcWeapon,
                entityIndex);
        const bool rotateNpcAmmo =
            npcEquipment.ammo.exists[entityIndex] &&
            npcEquipment.ammo.base.facing.dirty[entityIndex] &&
            npcWeapon.type[entityIndex] == WeaponType::Ranged;
        rotateEquipment(
            npcEquipment,
            entityIndex,
            rotateNpcWeapon,
            rotateNpcAmmo,
            useRotationAnimationStart);
    }
}
