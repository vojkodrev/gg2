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

    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!ctx.data.npc.active[i])
            continue;

        auto &npcWeapon = ctx.data.npc.equipment.weapon;
        const bool npcWeaponNeedsReset =
            npcWeapon.exists[i] &&
            (npcWeapon.base.facing.dirty[i] ||
             isRotationAnimationRunning(npcWeapon.base, i) ||
             isRotationAnimationFinished(npcWeapon.base, i) ||
             shouldUseRotationAnimationStart(ctx.data.npc.ai, npcWeapon, i) ||
             shouldClearRotationAnimationStart(ctx.data.npc.ai, npcWeapon, i));
        if (npcWeaponNeedsReset)
            scaleEntityBaseLocations(npcWeapon.base, i);
        if (ctx.data.npc.equipment.ammo.exists[i] &&
            ctx.data.npc.equipment.ammo.base.facing.dirty[i])
            scaleEntityBaseLocations(ctx.data.npc.equipment.ammo.base, i);
    }

    if (playerWeaponNeedsReset)
        for (int f = 0; f < playerWeapon.base.animation.frameCount[0]; f++)
            scaleAnchorLocation(
                playerWeapon.ranged.ammoAnchor,
                playerWeapon.base.scale.value[0],
                0,
                f);

    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!ctx.data.npc.active[i])
            continue;

        auto &npcWeapon = ctx.data.npc.equipment.weapon;
        const bool npcWeaponNeedsReset =
            npcWeapon.exists[i] &&
            (npcWeapon.base.facing.dirty[i] ||
             isRotationAnimationRunning(npcWeapon.base, i) ||
             isRotationAnimationFinished(npcWeapon.base, i) ||
             shouldUseRotationAnimationStart(ctx.data.npc.ai, npcWeapon, i) ||
             shouldClearRotationAnimationStart(ctx.data.npc.ai, npcWeapon, i));
        if (!npcWeaponNeedsReset)
            continue;

        for (int f = 0; f < npcWeapon.base.animation.frameCount[i]; f++)
            scaleAnchorLocation(
                npcWeapon.ranged.ammoAnchor,
                npcWeapon.base.scale.value[i],
                i,
                f);
    }
}
