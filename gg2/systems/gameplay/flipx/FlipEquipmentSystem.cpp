#include "FlipEquipmentSystem.h"
#include "UpdateEntityAnchorAndCollisionFlip.h"
#include "UpdateWeaponFlip.h"
#include <cstdint>

void flipEquipmentSystem(Context &ctx)
{
    updateWeaponFlip(ctx.data.player.facing, ctx.data.player.equipment.weapon.facing, 0);
    updateEntityAnchorAndCollisionFlip(
        ctx.data.player.equipment.weapon.animation,
        0,
        ctx.data.player.equipment.weapon.position.w[0],
        ctx.data.player.equipment.weapon.facing.flipX[0]);

    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
    {
        updateWeaponFlip(ctx.data.npc.facing, ctx.data.npc.equipment.weapon.facing, i);
        updateEntityAnchorAndCollisionFlip(
            ctx.data.npc.equipment.weapon.animation,
            i,
            ctx.data.npc.equipment.weapon.position.w[i],
            ctx.data.npc.equipment.weapon.facing.flipX[i]);
    }
}
