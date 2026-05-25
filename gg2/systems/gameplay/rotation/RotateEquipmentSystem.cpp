#include "RotateEquipmentSystem.h"
#include "RotateEntityBase.h"
#include <cstdint>

void rotateEquipmentSystem(Context &ctx)
{
    auto &playerAmmo = ctx.data.player.equipment.ammo;
    rotateEntityBase(playerAmmo.base, 0);

    auto &playerWeapon = ctx.data.player.equipment.weapon;
    rotateEntityBase(playerWeapon.base, 0);

    auto &npcAmmo = ctx.data.npc.equipment.ammo;
    auto &npcWeapon = ctx.data.npc.equipment.weapon;
    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
    {
        rotateEntityBase(npcAmmo.base, i);
        rotateEntityBase(npcWeapon.base, i);
    }
}
