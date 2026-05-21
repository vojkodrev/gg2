#include "FlipXSystem.h"
#include "UpdateEntityFlip.h"
#include "UpdateWeaponFlip.h"

void flipXSystem(Context &ctx)
{
    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
    {
        updateEntityFlip(ctx.data.npc.facing, i);
        updateWeaponFlip(ctx.data.npc.facing, ctx.data.npc.equipment.weapon.facing, i);
    }
}
