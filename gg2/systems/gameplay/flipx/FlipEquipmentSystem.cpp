#include "FlipEquipmentSystem.h"
#include "MirrorAnchorOffsetX.h"
#include "MirrorEntityAnchorsAndCollisionOffsets.h"
#include <cstdint>

void flipEquipmentSystem(Context &ctx)
{
    if (ctx.data.player.equipment.weapon.base.facing.dirty[0])
    {
        mirrorEntityAnchorsAndCollisionOffsets(
            ctx.data.player.equipment.weapon.base,
            0);
        if (ctx.data.player.equipment.weapon.base.facing.flipX[0])
        {
            mirrorAnchorOffsetX(
                ctx.data.player.equipment.weapon.ammoAnchor,
                ctx.data.player.equipment.weapon.base.position.w[0],
                0,
                0);
        }
    }
    if (ctx.data.player.equipment.ammo.base.facing.dirty[0])
    {
        mirrorEntityAnchorsAndCollisionOffsets(
            ctx.data.player.equipment.ammo.base,
            0);
    }

    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
    {
        if (ctx.data.npc.equipment.weapon.base.facing.dirty[i])
        {
            mirrorEntityAnchorsAndCollisionOffsets(
                ctx.data.npc.equipment.weapon.base,
                i);
            if (ctx.data.npc.equipment.weapon.base.facing.flipX[i])
            {
                mirrorAnchorOffsetX(
                    ctx.data.npc.equipment.weapon.ammoAnchor,
                    ctx.data.npc.equipment.weapon.base.position.w[i],
                    i,
                    0);
            }
        }
        if (ctx.data.npc.equipment.ammo.base.facing.dirty[i])
        {
            mirrorEntityAnchorsAndCollisionOffsets(
                ctx.data.npc.equipment.ammo.base,
                i);
        }
    }
}
