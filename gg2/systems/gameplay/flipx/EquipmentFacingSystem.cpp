#include "EquipmentFacingSystem.h"
#include "SyncFlipFromParentFacingAndMarkDirty.h"
#include <cstdint>

void equipmentFacingSystem(Context &ctx)
{
    if (ctx.data.player.base.facing.dirty[0])
    {
        if (ctx.data.player.equipment.weapon.exists[0])
            syncFlipFromParentFacingAndMarkDirty(
                ctx.data.player.base.facing,
                ctx.data.player.equipment.weapon.base.facing,
                0);

        if (ctx.data.player.equipment.ammo.exists[0])
            syncFlipFromParentFacingAndMarkDirty(
                ctx.data.player.base.facing,
                ctx.data.player.equipment.ammo.base.facing,
                0);
    }

    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!ctx.data.npc.active[i])
            continue;

        if (!ctx.data.npc.base.facing.dirty[i])
            continue;

        if (ctx.data.npc.equipment.weapon.exists[i])
            syncFlipFromParentFacingAndMarkDirty(
                ctx.data.npc.base.facing,
                ctx.data.npc.equipment.weapon.base.facing,
                i);

        if (ctx.data.npc.equipment.ammo.exists[i])
            syncFlipFromParentFacingAndMarkDirty(
                ctx.data.npc.base.facing,
                ctx.data.npc.equipment.ammo.base.facing,
                i);
    }
}
