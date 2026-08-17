#include "FlipEquipmentSystem.h"
#include "MirrorAnchorOffsetX.h"
#include "MirrorEntityAnchorsAndCollisionOffsets.h"
#include "../rotation/ShouldClearRotationAnimationStart.h"
#include "../rotation/IsRotationAnimationFinished.h"
#include "../rotation/IsRotationAnimationRunning.h"
#include "../rotation/ShouldUseRotationAnimationStart.h"
#include <cstdint>

void flipEquipmentSystem(Context &ctx)
{
    auto &playerWeapon = ctx.data.player.equipment.weapon;
    const bool playerWeaponNeedsMirror =
        playerWeapon.exists[0] &&
        (playerWeapon.base.facing.dirty[0] ||
         isRotationAnimationRunning(playerWeapon.base, 0) ||
         isRotationAnimationFinished(playerWeapon.base, 0));
    if (playerWeaponNeedsMirror && playerWeapon.base.facing.flipX[0])
    {
        mirrorEntityAnchorsAndCollisionOffsets(
            playerWeapon.base,
            0);
        if (playerWeapon.type[0] == WeaponType::Ranged)
            for (int frameIndex = 0;
                frameIndex < playerWeapon.base.animation.frameCount[0];
                frameIndex++)
                mirrorAnchorOffsetX(
                    playerWeapon.ranged.ammoAnchor,
                    playerWeapon.base.position.w[0],
                    0,
                    frameIndex,
                    0);
    }
    if (ctx.data.player.equipment.ammo.exists[0] &&
        ctx.data.player.equipment.ammo.base.facing.dirty[0])
    {
        mirrorEntityAnchorsAndCollisionOffsets(
            ctx.data.player.equipment.ammo.base,
            0);
    }

    for (uint32_t entityIndex = 0; entityIndex < MAX_NPCS; entityIndex++)
    {
        if (!ctx.data.npc.active[entityIndex])
            continue;

        auto &npcWeapon = ctx.data.npc.equipment.weapon;
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
        if (npcWeaponNeedsMirror &&
            npcWeapon.base.facing.flipX[entityIndex])
        {
            mirrorEntityAnchorsAndCollisionOffsets(
                npcWeapon.base,
                entityIndex);
            if (npcWeapon.type[entityIndex] == WeaponType::Ranged)
                for (int frameIndex = 0;
                    frameIndex <
                        npcWeapon.base.animation.frameCount[entityIndex];
                    frameIndex++)
                    mirrorAnchorOffsetX(
                        npcWeapon.ranged.ammoAnchor,
                        npcWeapon.base.position.w[entityIndex],
                        entityIndex,
                        frameIndex,
                        0);
        }
        if (ctx.data.npc.equipment.ammo.exists[entityIndex] &&
            ctx.data.npc.equipment.ammo.base.facing.dirty[entityIndex])
        {
            mirrorEntityAnchorsAndCollisionOffsets(
                ctx.data.npc.equipment.ammo.base,
                entityIndex);
        }
    }
}
