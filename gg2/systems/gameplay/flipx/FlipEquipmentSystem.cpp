#include "FlipEquipmentSystem.h"
#include "UpdateEntityAnchorAndCollisionFlipByParentFacing.h"
#include <cstdint>

void flipEquipmentSystem(Context &ctx)
{
    updateEntityAnchorAndCollisionFlipByParentFacing(
        ctx.data.player.base.facing,
        ctx.data.player.equipment.ammo.base,
        0);
    updateEntityAnchorAndCollisionFlipByParentFacing(
        ctx.data.player.base.facing,
        ctx.data.player.equipment.weapon.base,
        0);

    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
    {
        updateEntityAnchorAndCollisionFlipByParentFacing(
            ctx.data.npc.base.facing,
            ctx.data.npc.equipment.ammo.base,
            i);
        updateEntityAnchorAndCollisionFlipByParentFacing(
            ctx.data.npc.base.facing,
            ctx.data.npc.equipment.weapon.base,
            i);
    }
}
