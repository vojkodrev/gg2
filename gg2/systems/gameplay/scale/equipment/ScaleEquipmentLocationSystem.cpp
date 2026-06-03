#include "ScaleEquipmentLocationSystem.h"
#include "../ScaleAnchorLocation.h"
#include "../ScaleEntityBaseLocations.h"

void scaleEquipmentLocationSystem(Context &ctx)
{
    scaleEntityBaseLocations(ctx.data.player.equipment.weapon.base, 0);
    scaleEntityBaseLocations(ctx.data.player.equipment.ammo.base, 0);

    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
    {
        scaleEntityBaseLocations(ctx.data.npc.equipment.weapon.base, i);
        scaleEntityBaseLocations(ctx.data.npc.equipment.ammo.base, i);
    }

    scaleAnchorLocation(
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
    }
}
