#include "ScaleEquipmentLocationSystem.h"
#include "../rotation/ShouldClearRotationAnimationStart.h"
#include "../rotation/IsRotationAnimationFinished.h"
#include "../rotation/IsRotationAnimationRunning.h"
#include "../rotation/ShouldUseRotationAnimationStart.h"
#include "ScaleAnchorLocation.h"
#include "ScaleEntityBaseLocations.h"

void scaleEquipmentLocationSystem(Context &ctx)
{
    auto &playerWeapon = ctx.data.player.equipment.weapon;
    const bool playerWeaponNeedsReset =
        playerWeapon.exists[0] &&
        (playerWeapon.base.facing.dirty[0] ||
         isRotationAnimationRunning(playerWeapon.base, 0) ||
         isRotationAnimationFinished(playerWeapon.base, 0));
    if (playerWeaponNeedsReset)
        scaleEntityBaseLocations(playerWeapon.base, 0);
    if (ctx.data.player.equipment.ammo.exists[0] &&
        ctx.data.player.equipment.ammo.base.facing.dirty[0])
        scaleEntityBaseLocations(ctx.data.player.equipment.ammo.base, 0);

    for (uint32_t entityIndex = 0; entityIndex < MAX_NPCS; entityIndex++)
    {
        if (!ctx.data.npc.active[entityIndex])
            continue;

        auto &npcWeapon = ctx.data.npc.equipment.weapon;
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
        if (npcWeaponNeedsReset)
            scaleEntityBaseLocations(npcWeapon.base, entityIndex);
        if (ctx.data.npc.equipment.ammo.exists[entityIndex] &&
            ctx.data.npc.equipment.ammo.base.facing.dirty[entityIndex])
            scaleEntityBaseLocations(
                ctx.data.npc.equipment.ammo.base,
                entityIndex);
    }

    if (playerWeaponNeedsReset)
        for (int frameIndex = 0;
            frameIndex < playerWeapon.base.animation.frameCount[0];
            frameIndex++)
            scaleAnchorLocation(
                playerWeapon.ranged.ammoAnchor,
                playerWeapon.base.scale.value[0],
                0,
                frameIndex,
                0);

    for (uint32_t entityIndex = 0; entityIndex < MAX_NPCS; entityIndex++)
    {
        if (!ctx.data.npc.active[entityIndex])
            continue;

        auto &npcWeapon = ctx.data.npc.equipment.weapon;
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
        if (!npcWeaponNeedsReset)
            continue;

        for (int frameIndex = 0;
            frameIndex < npcWeapon.base.animation.frameCount[entityIndex];
            frameIndex++)
            scaleAnchorLocation(
                npcWeapon.ranged.ammoAnchor,
                npcWeapon.base.scale.value[entityIndex],
                entityIndex,
                frameIndex,
                0);
    }
}
