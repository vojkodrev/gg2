#include "MoveEquipmentSystem.h"
#include "UpdateWeaponPosition.h"

void moveEquipmentSystem(Context &ctx)
{
    updateWeaponPosition(ctx.data.player.equipment.weapon, ctx.data.player.base.animation, ctx.data.player.base.position, 0);

    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
        updateWeaponPosition(ctx.data.npc.equipment.weapon, ctx.data.npc.base.animation, ctx.data.npc.base.position, i);
}
