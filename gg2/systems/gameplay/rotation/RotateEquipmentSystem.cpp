#include "RotateEquipmentSystem.h"
#include "UpdateEntityAnchorAndCollisionRotation.h"
#include <cstdint>

void rotateEquipmentSystem(Context &ctx)
{
    auto &playerWeapon = ctx.data.player.equipment.weapon;
    if (playerWeapon.animation.frameCount[0] > 0)
    {
        playerWeapon.rotation.rotate[0] = playerWeapon.facing.flipX[0]
            ? -playerWeapon.rotation.initialRotate[0]
            : playerWeapon.rotation.initialRotate[0];
        float playerWeaponAngle = playerWeapon.rotation.rotate[0];
        updateEntityAnchorAndCollisionRotation(
            playerWeapon.animation,
            0,
            playerWeapon.position.w[0],
            playerWeapon.position.h[0],
            playerWeaponAngle);
    }

    auto &npcWeapon = ctx.data.npc.equipment.weapon;
    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
    {
        if (npcWeapon.animation.frameCount[i] == 0)
            continue;

        npcWeapon.rotation.rotate[i] = npcWeapon.facing.flipX[i]
            ? -npcWeapon.rotation.initialRotate[i]
            : npcWeapon.rotation.initialRotate[i];
        float npcWeaponAngle = npcWeapon.rotation.rotate[i];
        updateEntityAnchorAndCollisionRotation(
            npcWeapon.animation,
            i,
            npcWeapon.position.w[i],
            npcWeapon.position.h[i],
            npcWeaponAngle);
    }
}
