#pragma once
#include "../../../structs/equipment/Weapon.h"
#include <cstdint>

template<int N>
inline void updateEquipmentAnchorAndCollisionFlip(Weapon<N> &weaponData, uint32_t i)
{
    auto &weapon = weaponData.animation;
    if (!weaponData.facing.flipX[i])
        return;

    for (int f = 0; f < weapon.frameCount[i]; f++)
    {
        float frameW = weapon.frame.src.w[i][f] * weaponData.scale[i];
        weapon.frame.anchor.offX[i][f] = frameW - weapon.frame.anchor.offX[i][f] - weapon.frame.anchor.w[i][f];
        weapon.frame.collision.offX[i][f] = frameW - weapon.frame.collision.offX[i][f] - weapon.frame.collision.w[i][f];
    }
}
