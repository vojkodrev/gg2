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
        playerWeapon.base.facing.dirty[0] ||
        isRotationAnimationRunning(playerWeapon.base, 0) ||
        isRotationAnimationFinished(playerWeapon.base, 0))
    {
        rotateEntityBase(playerWeapon.base, 0);
        if (playerWeapon.type[0] == WeaponType::Ranged)
            for (int f = 0; f < playerWeapon.base.animation.frameCount[0]; f++)
                rotateRectCenter(
                    playerWeapon.ammoAnchor.offX[0][f],
                    playerWeapon.ammoAnchor.offY[0][f],
                    playerWeapon.ammoAnchor.w[0][f],
                    playerWeapon.ammoAnchor.h[0][f],
                    playerWeapon.base.position.w[0] * 0.5f,
                    playerWeapon.base.position.h[0] * 0.5f,
                    playerWeapon.base.rotation.rotate[0]);
    }

    auto &playerAmmo = ctx.data.player.equipment.ammo;
    if (playerAmmo.base.facing.dirty[0] && playerWeapon.type[0] == WeaponType::Ranged)
        rotateEntityBase(playerAmmo.base, 0);

    auto &npcAmmo = ctx.data.npc.equipment.ammo;
    auto &npcWeapon = ctx.data.npc.equipment.weapon;
    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!ctx.data.npc.active[i])
            continue;

        const bool npcWeaponRotationRunning = isRotationAnimationRunning(npcWeapon.base, i);
        const bool npcWeaponRotationFinished = isRotationAnimationFinished(npcWeapon.base, i);
        const bool useRotationAnimationStart =
            shouldUseRotationAnimationStart(ctx.data.npc.ai, npcWeapon, i);

        if (
            npcWeapon.base.facing.dirty[i] ||
            npcWeaponRotationRunning ||
            npcWeaponRotationFinished ||
            useRotationAnimationStart ||
            shouldClearRotationAnimationStart(ctx.data.npc.ai, npcWeapon, i))
        {
            rotateEntityBase(npcWeapon.base, i, useRotationAnimationStart);
            if (npcWeapon.type[i] == WeaponType::Ranged)
                for (int f = 0; f < npcWeapon.base.animation.frameCount[i]; f++)
                    rotateRectCenter(
                        npcWeapon.ammoAnchor.offX[i][f],
                        npcWeapon.ammoAnchor.offY[i][f],
                        npcWeapon.ammoAnchor.w[i][f],
                        npcWeapon.ammoAnchor.h[i][f],
                        npcWeapon.base.position.w[i] * 0.5f,
                        npcWeapon.base.position.h[i] * 0.5f,
                        npcWeapon.base.rotation.rotate[i]);
        }
        if (npcAmmo.base.facing.dirty[i] && npcWeapon.type[i] == WeaponType::Ranged)
            rotateEntityBase(npcAmmo.base, i);
    }
}
