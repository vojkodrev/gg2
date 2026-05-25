#include "FlipEquipmentSystem.h"
#include "UpdateEntityAnchorAndCollisionFlip.h"
#include "UpdateWeaponFlip.h"
#include <cstdint>

void flipEquipmentSystem(Context &ctx)
{
    updateWeaponFlip(ctx.data.player.base.facing, ctx.data.player.equipment.weapon.base.facing, 0);
    updateEntityAnchorAndCollisionFlip(ctx.data.player.equipment.weapon.base, 0);

    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
    {
        updateWeaponFlip(ctx.data.npc.base.facing, ctx.data.npc.equipment.weapon.base.facing, i);
        updateEntityAnchorAndCollisionFlip(ctx.data.npc.equipment.weapon.base, i);
    }
}
