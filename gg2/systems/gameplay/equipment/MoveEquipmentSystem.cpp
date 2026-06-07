#include "MoveEquipmentSystem.h"
#include "AlignAmmoToWeaponAnchor.h"

void moveEquipmentSystem(Context &ctx)
{
    alignEquipmentToParentAnchor(
        ctx.data.player.equipment.weapon.base,
        ctx.data.player.base.animation,
        ctx.data.player.base.position,
        0);
    alignAmmoToWeaponAnchor(
        ctx.data.player.equipment.ammo.base,
        ctx.data.player.equipment.weapon.ammoAnchor,
        ctx.data.player.equipment.weapon.base,
        ctx.data.player.base,
        0);

    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
    {
        alignEquipmentToParentAnchor(
            ctx.data.npc.equipment.weapon.base,
            ctx.data.npc.base.animation,
            ctx.data.npc.base.position,
            i);
        alignAmmoToWeaponAnchor(
            ctx.data.npc.equipment.ammo.base,
            ctx.data.npc.equipment.weapon.ammoAnchor,
            ctx.data.npc.equipment.weapon.base,
            ctx.data.npc.base,
            i);
    }
}
