#include "EquipmentFacingSystem.h"
#include "SyncFlipFromParentFacingAndMarkDirty.h"
#include <cstdint>

void equipmentFacingSystem(Context &ctx)
{
    if (ctx.data.player.base.facing.dirty[0])
    {
        syncFlipFromParentFacingAndMarkDirty(
            ctx.data.player.base.facing,
            ctx.data.player.equipment.weapon.base.facing,
            0);

        syncFlipFromParentFacingAndMarkDirty(
            ctx.data.player.base.facing,
            ctx.data.player.equipment.ammo.base.facing,
            0);
    }

    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
    {
        if (!ctx.data.npc.base.facing.dirty[i])
            continue;

        syncFlipFromParentFacingAndMarkDirty(
            ctx.data.npc.base.facing,
            ctx.data.npc.equipment.weapon.base.facing,
            i);

        syncFlipFromParentFacingAndMarkDirty(
            ctx.data.npc.base.facing,
            ctx.data.npc.equipment.ammo.base.facing,
            i);
    }
}
