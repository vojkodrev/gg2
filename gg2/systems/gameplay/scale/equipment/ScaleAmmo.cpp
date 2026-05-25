#include "ScaleAmmo.h"
#include "../ScaleEntityBase.h"
#include <cstdint>

void scaleAmmo(Context &ctx)
{
    auto &playerAmmo = ctx.data.player.equipment.ammo;
    scaleEntityBase(playerAmmo.base, 0);

    auto &npcAmmo = ctx.data.npc.equipment.ammo;
    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
        scaleEntityBase(npcAmmo.base, i);
}
