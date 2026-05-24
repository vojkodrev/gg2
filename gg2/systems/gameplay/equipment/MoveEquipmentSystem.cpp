#include "MoveEquipmentSystem.h"
#include "UpdateWeaponPosition.h"

void moveEquipmentSystem(Context &ctx)
{
    updateWeaponPosition(ctx.data.player.equipment.weapon, ctx.data.player.animation, ctx.data.player.position, 0);

    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
        updateWeaponPosition(ctx.data.npc.equipment.weapon, ctx.data.npc.animation, ctx.data.npc.position, i);
}
