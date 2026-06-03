#include "ScaleEquipmentSystem.h"
#include "ScaleEquipmentEntity.h"
#include "../ScaleAnchorLocation.h"
#include "../ScaleAnchorSize.h"

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

    scaleAnchorLocation(
        ctx.data.player.equipment.weapon.ammoAnchor,
        ctx.data.player.equipment.weapon.base.scale[0],
        0,
        0);
    scaleAnchorSize(
        ctx.data.player.equipment.weapon.ammoAnchor,
        ctx.data.player.equipment.weapon.base.scale[0],
        0,
        0);

    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
    {
        scaleAnchorLocation(
            ctx.data.npc.equipment.weapon.ammoAnchor,
            ctx.data.npc.equipment.weapon.base.scale[i],
            i,
            0);
        scaleAnchorSize(
            ctx.data.npc.equipment.weapon.ammoAnchor,
            ctx.data.npc.equipment.weapon.base.scale[i],
            i,
            0);
    }
}
