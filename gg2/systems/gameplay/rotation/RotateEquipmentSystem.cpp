#include "RotateEquipmentSystem.h"
#include "UpdateEntityAnchorAndCollisionRotation.h"
#include <cstdint>

void rotateEquipmentSystem(Context &ctx)
{
    auto &playerWeapon = ctx.data.player.equipment.weapon;
    if (playerWeapon.animation.frameCount[0] > 0)
    {
        float playerAngle = playerWeapon.facing.flipX[0] ? -playerWeapon.rotation.rotate[0] : playerWeapon.rotation.rotate[0];
        updateEntityAnchorAndCollisionRotation(
            playerWeapon.animation,
            0,
            playerWeapon.position.w[0],
            playerWeapon.position.h[0],
            playerAngle);
    }

    auto &npcWeapon = ctx.data.npc.equipment.weapon;
    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
    {
        if (npcWeapon.animation.frameCount[i] == 0)
            continue;

        float npcAngle = npcWeapon.facing.flipX[i] ? -npcWeapon.rotation.rotate[i] : npcWeapon.rotation.rotate[i];
        updateEntityAnchorAndCollisionRotation(
            npcWeapon.animation,
            i,
            npcWeapon.position.w[i],
            npcWeapon.position.h[i],
            npcAngle);
    }
}
