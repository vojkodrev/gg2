#include "ScaleWeapon.h"
#include "../ScaleEntityBase.h"
#include <cstdint>

void scaleWeapon(Context &ctx)
{
    auto &playerWeapon = ctx.data.player.equipment.weapon;
    scaleEntityBase(playerWeapon.base, 0);

    auto &npcWeapon = ctx.data.npc.equipment.weapon;
    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
        scaleEntityBase(npcWeapon.base, i);
}
