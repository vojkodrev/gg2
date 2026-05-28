#include "ScaleEquipmentSystem.h"
#include "ScaleEquipmentEntity.h"
#include "../ScaleAnchor.h"

void scaleEquipmentSystem(Context &ctx)
{
    scaleEquipmentEntity(
        ctx.data.player.equipment.weapon.base,
        ctx.data.npc.equipment.weapon.base,
        ctx.data.npc.npcCount);
    scaleEquipmentEntity(
        ctx.data.player.equipment.ammo.base,
        ctx.data.npc.equipment.ammo.base,
        ctx.data.npc.npcCount);

    scaleAnchor(
        ctx.data.player.equipment.weapon.ammoAnchor,
        ctx.data.player.equipment.weapon.base.scale[0],
        0,
        0);

    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
    {
        scaleAnchor(
            ctx.data.npc.equipment.weapon.ammoAnchor,
            ctx.data.npc.equipment.weapon.base.scale[i],
            i,
            0);
    }
}
