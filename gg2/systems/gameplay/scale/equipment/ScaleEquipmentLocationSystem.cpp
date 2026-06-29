#include "ScaleEquipmentLocationSystem.h"
#include "../ScaleAnchorLocation.h"
#include "../ScaleEntityBaseLocations.h"

void scaleEquipmentLocationSystem(Context &ctx)
{
    if (ctx.data.player.equipment.weapon.base.facing.dirty[0])
        scaleEntityBaseLocations(ctx.data.player.equipment.weapon.base, 0);
    if (ctx.data.player.equipment.ammo.base.facing.dirty[0])
        scaleEntityBaseLocations(ctx.data.player.equipment.ammo.base, 0);

    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!ctx.data.npc.active[i])
            continue;

        if (ctx.data.npc.equipment.weapon.base.facing.dirty[i])
            scaleEntityBaseLocations(ctx.data.npc.equipment.weapon.base, i);
        if (ctx.data.npc.equipment.ammo.base.facing.dirty[i])
            scaleEntityBaseLocations(ctx.data.npc.equipment.ammo.base, i);
    }

    if (ctx.data.player.equipment.weapon.base.facing.dirty[0])
    {
        scaleAnchorLocation(
            ctx.data.player.equipment.weapon.ammoAnchor,
            ctx.data.player.equipment.weapon.base.scale.value[0],
            0,
            0);
    }

    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!ctx.data.npc.active[i])
            continue;

        if (!ctx.data.npc.equipment.weapon.base.facing.dirty[i])
            continue;

        scaleAnchorLocation(
            ctx.data.npc.equipment.weapon.ammoAnchor,
            ctx.data.npc.equipment.weapon.base.scale.value[i],
            i,
            0);
    }
}
