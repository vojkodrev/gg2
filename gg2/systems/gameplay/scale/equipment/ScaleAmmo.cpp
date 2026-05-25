#include "ScaleAmmo.h"
#include "../ScaleAnimationFrames.h"
#include "../ScaleEntityBasePosition.h"
#include <cstdint>

void scaleAmmo(Context &ctx)
{
    auto &playerAmmo = ctx.data.player.equipment.ammo;
    scaleEntityBasePosition(playerAmmo.base, 0);
    scaleAnimationFrames(playerAmmo.base.animation, playerAmmo.base.scale, 1);

    auto &npcAmmo = ctx.data.npc.equipment.ammo;
    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
        scaleEntityBasePosition(npcAmmo.base, i);
    scaleAnimationFrames(npcAmmo.base.animation, npcAmmo.base.scale, ctx.data.npc.npcCount);
}
