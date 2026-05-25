#include "ScaleEquipmentSystem.h"
#include "ScaleEquipmentEntity.h"

void scaleEquipmentSystem(Context &ctx)
{
    scaleEquipmentEntity(
        ctx.data.player.equipment.ammo.base,
        ctx.data.npc.equipment.ammo.base,
        ctx.data.npc.npcCount);
    scaleEquipmentEntity(
        ctx.data.player.equipment.weapon.base,
        ctx.data.npc.equipment.weapon.base,
        ctx.data.npc.npcCount);
}
