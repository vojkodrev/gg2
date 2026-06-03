#include "ScaleEquipmentSizeSystem.h"
#include "../ScaleAnchorSize.h"
#include "../ScaleEntityBaseSizes.h"

void scaleEquipmentSizeSystem(Context &ctx)
{
    scaleEntityBaseSizes(ctx.data.player.equipment.weapon.base, 0);
    scaleEntityBaseSizes(ctx.data.player.equipment.ammo.base, 0);

    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
    {
        scaleEntityBaseSizes(ctx.data.npc.equipment.weapon.base, i);
        scaleEntityBaseSizes(ctx.data.npc.equipment.ammo.base, i);
    }

    scaleAnchorSize(
        ctx.data.player.equipment.weapon.ammoAnchor,
        ctx.data.player.equipment.weapon.base.scale[0],
        0,
        0);

    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
    {
        scaleAnchorSize(
            ctx.data.npc.equipment.weapon.ammoAnchor,
            ctx.data.npc.equipment.weapon.base.scale[i],
            i,
            0);
    }
}
