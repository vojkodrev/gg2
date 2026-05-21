#include "MoveEquipmentSystem.h"
#include "UpdateWeapon.h"

void moveEquipmentSystem(Context &ctx)
{
    updateWeapon(ctx.data.player.equipment.weapon, ctx.data.player.animation, ctx.data.player.position, ctx.data.player.facing, 0);

    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
        updateWeapon(ctx.data.npc.equipment.weapon, ctx.data.npc.animation, ctx.data.npc.position, ctx.data.npc.facing, i);
}
