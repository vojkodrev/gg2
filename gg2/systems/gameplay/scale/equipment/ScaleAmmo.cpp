#include "ScaleAmmo.h"
#include "ScaleEquipmentSize.h"
#include "../ScaleAnimationFrames.h"
#include <cstdint>

void scaleAmmo(Context &ctx)
{
    auto &playerAmmo = ctx.data.player.equipment.ammo;
    scaleEquipmentSize(playerAmmo.position, playerAmmo.scale, playerAmmo.animation.frameCount, 0);
    scaleAnimationFrames(playerAmmo.animation, playerAmmo.scale, 1);

    auto &npcAmmo = ctx.data.npc.equipment.ammo;
    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
        scaleEquipmentSize(npcAmmo.position, npcAmmo.scale, npcAmmo.animation.frameCount, i);
    scaleAnimationFrames(npcAmmo.animation, npcAmmo.scale, ctx.data.npc.npcCount);
}
