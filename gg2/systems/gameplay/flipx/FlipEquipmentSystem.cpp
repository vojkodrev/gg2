#include "FlipEquipmentSystem.h"
#include "UpdateWeaponAnchorCollisionFlip.h"
#include <cstdint>

void flipEquipmentSystem(Context &ctx)
{
    updateWeaponAnchorCollisionFlip(
        ctx.data.player.base.facing,
        ctx.data.player.equipment.weapon.base,
        0);

    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
    {
        updateWeaponAnchorCollisionFlip(
            ctx.data.npc.base.facing,
            ctx.data.npc.equipment.weapon.base,
            i);
    }
}
