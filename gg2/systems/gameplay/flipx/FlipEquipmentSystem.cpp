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
        playerWeapon.base.facing.dirty[0] ||
        isRotationAnimationRunning(playerWeapon.base, 0) ||
        isRotationAnimationFinished(playerWeapon.base, 0);
    if (playerWeaponNeedsMirror && playerWeapon.base.facing.flipX[0])
    {
        mirrorEntityAnchorsAndCollisionOffsets(
            playerWeapon.base,
            0);
        if (playerWeapon.type[0] == WeaponType::Ranged)
            for (int f = 0; f < playerWeapon.base.animation.frameCount[0]; f++)
                mirrorAnchorOffsetX(
                    playerWeapon.ranged.ammoAnchor,
                    playerWeapon.base.position.w[0],
                    0,
                    f);
    }
    if (ctx.data.player.equipment.ammo.base.facing.dirty[0])
    {
        mirrorEntityAnchorsAndCollisionOffsets(
            ctx.data.player.equipment.ammo.base,
            0);
    }

    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!ctx.data.npc.active[i])
            continue;

        auto &npcWeapon = ctx.data.npc.equipment.weapon;
        const bool npcWeaponNeedsMirror =
            npcWeapon.base.facing.dirty[i] ||
            isRotationAnimationRunning(npcWeapon.base, i) ||
            isRotationAnimationFinished(npcWeapon.base, i) ||
            shouldUseRotationAnimationStart(ctx.data.npc.ai, npcWeapon, i) ||
            shouldClearRotationAnimationStart(ctx.data.npc.ai, npcWeapon, i);
        if (npcWeaponNeedsMirror && npcWeapon.base.facing.flipX[i])
        {
            mirrorEntityAnchorsAndCollisionOffsets(
                npcWeapon.base,
                i);
            if (npcWeapon.type[i] == WeaponType::Ranged)
                for (int f = 0; f < npcWeapon.base.animation.frameCount[i]; f++)
                    mirrorAnchorOffsetX(
                        npcWeapon.ranged.ammoAnchor,
                        npcWeapon.base.position.w[i],
                        i,
                        f);
        }
        if (ctx.data.npc.equipment.ammo.base.facing.dirty[i])
        {
            mirrorEntityAnchorsAndCollisionOffsets(
                ctx.data.npc.equipment.ammo.base,
                i);
        }
    }
}
