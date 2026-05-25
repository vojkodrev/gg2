#include "RotateEquipmentSystem.h"
#include "UpdateWeaponRotation.h"
#include <cstdint>

void rotateEquipmentSystem(Context &ctx)
{
    auto &playerWeapon = ctx.data.player.equipment.weapon;
    updateWeaponRotation(playerWeapon.base, 0);

    auto &npcWeapon = ctx.data.npc.equipment.weapon;
    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
        updateWeaponRotation(npcWeapon.base, i);
}
