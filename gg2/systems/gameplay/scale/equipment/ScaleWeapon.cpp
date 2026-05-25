#include "ScaleWeapon.h"
#include "ScaleEquipmentSize.h"
#include "../ScaleAnimationFrames.h"
#include <cstdint>

void scaleWeapon(Context &ctx)
{
    auto &playerWeapon = ctx.data.player.equipment.weapon;
    scaleEquipmentSize(playerWeapon.position, playerWeapon.scale, playerWeapon.animation.frameCount, 0);
    scaleAnimationFrames(playerWeapon.animation, playerWeapon.scale, 1);

    auto &npcWeapon = ctx.data.npc.equipment.weapon;
    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
        scaleEquipmentSize(npcWeapon.position, npcWeapon.scale, npcWeapon.animation.frameCount, i);
    scaleAnimationFrames(npcWeapon.animation, npcWeapon.scale, ctx.data.npc.npcCount);
}
