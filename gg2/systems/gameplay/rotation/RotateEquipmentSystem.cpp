#include "RotateEquipmentSystem.h"
#include "RotateEntityBase.h"
#include "UpdateAnchorRotation.h"
#include <cstdint>

void rotateEquipmentSystem(Context &ctx)
{
    auto &playerWeapon = ctx.data.player.equipment.weapon;
    if (playerWeapon.base.facing.dirty[0])
    {
        rotateEntityBase(playerWeapon.base, 0);
        updateAnchorRotation(
            playerWeapon.ammoAnchor,
            playerWeapon.base,
            0,
            0);
    }

    auto &playerAmmo = ctx.data.player.equipment.ammo;
    if (playerAmmo.base.facing.dirty[0])
        rotateEntityBase(playerAmmo.base, 0);

    auto &npcAmmo = ctx.data.npc.equipment.ammo;
    auto &npcWeapon = ctx.data.npc.equipment.weapon;
    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
    {
        if (npcWeapon.base.facing.dirty[i])
        {
            rotateEntityBase(npcWeapon.base, i);
            updateAnchorRotation(
                npcWeapon.ammoAnchor,
                npcWeapon.base,
                i,
                0);
        }
        if (npcAmmo.base.facing.dirty[i])
            rotateEntityBase(npcAmmo.base, i);
    }
}
