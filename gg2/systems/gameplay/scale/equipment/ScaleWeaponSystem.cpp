#include "ScaleWeaponSystem.h"
#include "../ScaleAnimationFrames.h"
#include <cstdint>

void scaleWeaponSystem(Context &ctx)
{
    auto &playerWeapon = ctx.data.player.equipment.weapon;
    if (playerWeapon.animation.frameCount[0] > 0)
    {
        playerWeapon.position.w[0] = playerWeapon.position.initialW[0] * playerWeapon.scale[0];
        playerWeapon.position.h[0] = playerWeapon.position.initialH[0] * playerWeapon.scale[0];
    }
    scaleAnimationFrames(playerWeapon.animation, playerWeapon.scale, 1);

    auto &npcWeapon = ctx.data.npc.equipment.weapon;
    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
    {
        if (npcWeapon.animation.frameCount[i] == 0)
            continue;

        npcWeapon.position.w[i] = npcWeapon.position.initialW[i] * npcWeapon.scale[i];
        npcWeapon.position.h[i] = npcWeapon.position.initialH[i] * npcWeapon.scale[i];
    }
    scaleAnimationFrames(npcWeapon.animation, npcWeapon.scale, ctx.data.npc.npcCount);
}
