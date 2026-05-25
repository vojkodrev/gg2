#include "RotateEquipmentSystem.h"
#include "UpdateEntityAnchorAndCollisionRotation.h"
#include <cstdint>

void rotateEquipmentSystem(Context &ctx)
{
    auto &playerWeapon = ctx.data.player.equipment.weapon;
    if (playerWeapon.base.animation.frameCount[0] > 0)
    {
        playerWeapon.base.rotation.rotate[0] = playerWeapon.base.facing.flipX[0]
            ? -playerWeapon.base.rotation.initialRotate[0]
            : playerWeapon.base.rotation.initialRotate[0];
        float playerWeaponAngle = playerWeapon.base.rotation.rotate[0];
        updateEntityAnchorAndCollisionRotation(
            playerWeapon.base.animation,
            0,
            playerWeapon.base.position.w[0],
            playerWeapon.base.position.h[0],
            playerWeaponAngle);
    }

    auto &npcWeapon = ctx.data.npc.equipment.weapon;
    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
    {
        if (npcWeapon.base.animation.frameCount[i] == 0)
            continue;

        npcWeapon.base.rotation.rotate[i] = npcWeapon.base.facing.flipX[i]
            ? -npcWeapon.base.rotation.initialRotate[i]
            : npcWeapon.base.rotation.initialRotate[i];
        float npcWeaponAngle = npcWeapon.base.rotation.rotate[i];
        updateEntityAnchorAndCollisionRotation(
            npcWeapon.base.animation,
            i,
            npcWeapon.base.position.w[i],
            npcWeapon.base.position.h[i],
            npcWeaponAngle);
    }
}
