#include "RotateEquipmentSystem.h"
#include "ShouldClearRotationAnimationStart.h"
#include "IsRotationAnimationFinished.h"
#include "IsRotationAnimationRunning.h"
#include "RotateEntityBase.h"
#include "ShouldUseRotationAnimationStart.h"
#include "../../../utils/rect/RotateRectCenter.h"
#include <cstdint>

void rotateEquipmentSystem(Context &ctx)
{
    auto &playerWeapon = ctx.data.player.equipment.weapon;
    if (
        playerWeapon.exists[0] &&
        (playerWeapon.base.facing.dirty[0] ||
         isRotationAnimationRunning(playerWeapon.base, 0) ||
         isRotationAnimationFinished(playerWeapon.base, 0)))
    {
        rotateEntityBase(playerWeapon.base, 0);
        if (playerWeapon.type[0] == WeaponType::Ranged)
            for (int frameIndex = 0;
                frameIndex < playerWeapon.base.animation.frameCount[0];
                frameIndex++)
                rotateRectCenter(
                    playerWeapon.ranged.ammoAnchor.offX[0][frameIndex][0],
                    playerWeapon.ranged.ammoAnchor.offY[0][frameIndex][0],
                    playerWeapon.ranged.ammoAnchor.w[0][frameIndex][0],
                    playerWeapon.ranged.ammoAnchor.h[0][frameIndex][0],
                    playerWeapon.base.position.w[0] * 0.5f,
                    playerWeapon.base.position.h[0] * 0.5f,
                    playerWeapon.base.rotation.rotate[0]);
    }

    auto &playerAmmo = ctx.data.player.equipment.ammo;
    if (playerAmmo.exists[0] &&
        playerAmmo.base.facing.dirty[0] &&
        playerWeapon.type[0] == WeaponType::Ranged)
        rotateEntityBase(playerAmmo.base, 0);

    auto &npcAmmo = ctx.data.npc.equipment.ammo;
    auto &npcWeapon = ctx.data.npc.equipment.weapon;
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

        if (
            npcWeapon.base.facing.dirty[entityIndex] ||
            npcWeaponRotationRunning ||
            npcWeaponRotationFinished ||
            useRotationAnimationStart ||
            shouldClearRotationAnimationStart(
                ctx.data.npc.ai,
                npcWeapon,
                entityIndex))
        {
            rotateEntityBase(
                npcWeapon.base,
                entityIndex,
                useRotationAnimationStart);
            if (npcWeapon.type[entityIndex] == WeaponType::Ranged)
                for (int frameIndex = 0;
                    frameIndex <
                        npcWeapon.base.animation.frameCount[entityIndex];
                    frameIndex++)
                    rotateRectCenter(
                        npcWeapon.ranged.ammoAnchor
                            .offX[entityIndex][frameIndex][0],
                        npcWeapon.ranged.ammoAnchor
                            .offY[entityIndex][frameIndex][0],
                        npcWeapon.ranged.ammoAnchor
                            .w[entityIndex][frameIndex][0],
                        npcWeapon.ranged.ammoAnchor
                            .h[entityIndex][frameIndex][0],
                        npcWeapon.base.position.w[entityIndex] * 0.5f,
                        npcWeapon.base.position.h[entityIndex] * 0.5f,
                        npcWeapon.base.rotation.rotate[entityIndex]);
        }
        if (npcAmmo.exists[entityIndex] &&
            npcAmmo.base.facing.dirty[entityIndex] &&
            npcWeapon.type[entityIndex] == WeaponType::Ranged)
            rotateEntityBase(npcAmmo.base, entityIndex);
    }
}
