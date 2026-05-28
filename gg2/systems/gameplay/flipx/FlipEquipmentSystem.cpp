#include "FlipEquipmentSystem.h"
#include "UpdateAnchorOffsetFlip.h"
#include "UpdateEntityAnchorCollisionFlipByParentFacing.h"
#include <cstdint>

void flipEquipmentSystem(Context &ctx)
{
    updateEntityAnchorCollisionFlipByParentFacing(
        ctx.data.player.base.facing,
        ctx.data.player.equipment.weapon.base,
        0);
    if (ctx.data.player.equipment.weapon.base.facing.flipX[0])
    {
        updateAnchorOffsetFlip(
            ctx.data.player.equipment.weapon.ammoAnchor,
            ctx.data.player.equipment.weapon.base.position.w[0],
            0,
            0);
    }
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
        if (ctx.data.npc.equipment.weapon.base.facing.flipX[i])
        {
            updateAnchorOffsetFlip(
                ctx.data.npc.equipment.weapon.ammoAnchor,
                ctx.data.npc.equipment.weapon.base.position.w[i],
                i,
                0);
        }
        updateEntityAnchorCollisionFlipByParentFacing(
            ctx.data.npc.base.facing,
            ctx.data.npc.equipment.ammo.base,
            i);
    }
}
