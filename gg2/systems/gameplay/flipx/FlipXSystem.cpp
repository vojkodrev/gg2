#include "FlipXSystem.h"
#include "UpdateEntityFlip.h"
#include "UpdateWeaponFlip.h"

void flipXSystem(Context &ctx)
{
    updateEntityFlip(ctx.data.player.facing, 0);
    updateWeaponFlip(ctx.data.player.facing, ctx.data.player.equipment.weapon.facing, 0);

    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
    {
        updateEntityFlip(ctx.data.npc.facing, i);
        updateWeaponFlip(ctx.data.npc.facing, ctx.data.npc.equipment.weapon.facing, i);
    }
}
