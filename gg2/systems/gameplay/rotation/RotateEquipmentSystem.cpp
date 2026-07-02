#include "RotateEquipmentSystem.h"
#include "RotateEntityBase.h"
#include "RotateAnchorAroundEntityCenter.h"
#include <cstdint>

void rotateEquipmentSystem(Context &ctx)
{
    auto &playerWeapon = ctx.data.player.equipment.weapon;
    if (playerWeapon.base.facing.dirty[0])
    {
        rotateEntityBase(playerWeapon.base, 0);
        if (playerWeapon.type[0] == WeaponType::Ranged)
            rotateAnchorAroundEntityCenter(
                playerWeapon.ammoAnchor,
                playerWeapon.base,
                0,
                0);
    }

    auto &playerAmmo = ctx.data.player.equipment.ammo;
    if (
        playerAmmo.base.facing.dirty[0] &&
        playerWeapon.type[0] == WeaponType::Ranged)
        rotateEntityBase(playerAmmo.base, 0);

    auto &npcAmmo = ctx.data.npc.equipment.ammo;
    auto &npcWeapon = ctx.data.npc.equipment.weapon;
    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!ctx.data.npc.active[i])
            continue;

        if (npcWeapon.base.facing.dirty[i])
        {
            rotateEntityBase(npcWeapon.base, i);
            if (npcWeapon.type[i] == WeaponType::Ranged)
                rotateAnchorAroundEntityCenter(
                    npcWeapon.ammoAnchor,
                    npcWeapon.base,
                    i,
                    0);
        }
        if (
            npcAmmo.base.facing.dirty[i] &&
            npcWeapon.type[i] == WeaponType::Ranged)
            rotateEntityBase(npcAmmo.base, i);
    }
}
