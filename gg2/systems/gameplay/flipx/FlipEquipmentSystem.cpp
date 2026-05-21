#include "FlipEquipmentSystem.h"
#include "UpdateEquipmentAnchorAndCollisionFlip.h"
#include "UpdateWeaponFlip.h"
#include <cstdint>

void flipEquipmentSystem(Context &ctx)
{
    updateWeaponFlip(ctx.data.player.facing, ctx.data.player.equipment.weapon.facing, 0);
    updateEquipmentAnchorAndCollisionFlip(ctx.data.player.equipment.weapon, 0);

    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
    {
        updateWeaponFlip(ctx.data.npc.facing, ctx.data.npc.equipment.weapon.facing, i);
        updateEquipmentAnchorAndCollisionFlip(ctx.data.npc.equipment.weapon, i);
    }
}
