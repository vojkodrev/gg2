#include "ScaleWeapon.h"
#include "../ScaleAnimationFrames.h"
#include "../ScaleEntityBasePosition.h"
#include <cstdint>

void scaleWeapon(Context &ctx)
{
    auto &playerWeapon = ctx.data.player.equipment.weapon;
    scaleEntityBasePosition(playerWeapon.base, 0);
    scaleAnimationFrames(playerWeapon.base.animation, playerWeapon.base.scale, 1);

    auto &npcWeapon = ctx.data.npc.equipment.weapon;
    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
        scaleEntityBasePosition(npcWeapon.base, i);
    scaleAnimationFrames(npcWeapon.base.animation, npcWeapon.base.scale, ctx.data.npc.npcCount);
}
