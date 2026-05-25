#include "MoveEquipmentSystem.h"
#include "UpdateEquipmentEntityPosition.h"

void moveEquipmentSystem(Context &ctx)
{
    updateEquipmentEntityPosition(
        ctx.data.player.equipment.ammo.base,
        ctx.data.player.base.animation,
        ctx.data.player.base.position,
        0);
    updateEquipmentEntityPosition(
        ctx.data.player.equipment.weapon.base,
        ctx.data.player.base.animation,
        ctx.data.player.base.position,
        0);

    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
    {
        updateEquipmentEntityPosition(
            ctx.data.npc.equipment.ammo.base,
            ctx.data.npc.base.animation,
            ctx.data.npc.base.position,
            i);
        updateEquipmentEntityPosition(
            ctx.data.npc.equipment.weapon.base,
            ctx.data.npc.base.animation,
            ctx.data.npc.base.position,
            i);
    }
}
