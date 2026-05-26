#include "FlipEquipmentSystem.h"
#include "UpdateEntityAnchorCollisionFlipByParentFacing.h"
#include <cstdint>

void flipEquipmentSystem(Context &ctx)
{
    updateEntityAnchorCollisionFlipByParentFacing(
        ctx.data.player.base.facing,
        ctx.data.player.equipment.weapon.base,
        0);
    updateEntityAnchorCollisionFlipByParentFacing(
        ctx.data.player.base.facing,
        ctx.data.player.equipment.ammo.base,
        0);

    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
    {
        updateEntityAnchorCollisionFlipByParentFacing(
            ctx.data.npc.base.facing,
            ctx.data.npc.equipment.weapon.base,
            i);
        updateEntityAnchorCollisionFlipByParentFacing(
            ctx.data.npc.base.facing,
            ctx.data.npc.equipment.ammo.base,
            i);
    }
}
