#pragma once
#include "../../structs/equipment/Weapon.h"
#include "../../structs/core/EntityPosition.h"
#include "../../structs/core/Facing.h"
#include "../../structs/render/RenderBuffer.h"
#include "../../structs/core/constants/RenderConstants.h"
#include <cstdint>

template<int N>
inline void fillWeaponRenderBuffer(RenderBuffer &rb, const Weapon<N> &weaponData, const EntityPosition<N> &parentPosition, const Facing<N> &parentFacing, uint32_t parentEntityIndex, uint32_t parentRenderIndex, uint32_t groupId)
{
    const auto &weapon = weaponData.animation;
    const auto &weaponPos = weaponData.position;
    if (weapon.frameCount[parentEntityIndex] == 0)
        return;

    int wf = weapon.frameIndex[parentEntityIndex];
    uint32_t wn = rb.count++;

    rb.src.x[wn] = (float)weapon.frame.src.x[parentEntityIndex][wf];
    rb.src.y[wn] = (float)weapon.frame.src.y[parentEntityIndex][wf];
    rb.src.w[wn] = (float)weapon.frame.src.w[parentEntityIndex][wf];
    rb.src.h[wn] = (float)weapon.frame.src.h[parentEntityIndex][wf];

    rb.group.id[wn] = groupId;
    rb.group.zIndex[wn] = WEAPON_Z_INDEX;
    bool parentNeedsFlip = parentFacing.facing[parentEntityIndex] != weaponData.facing.initialFacing[parentEntityIndex];
    bool weaponFacingChanged = weaponData.facing.facing[parentEntityIndex] != weaponData.facing.initialFacing[parentEntityIndex];
    rb.flipX[wn] = parentNeedsFlip != weaponFacingChanged;

    rb.dst.x[wn] = parentPosition.x[parentEntityIndex] + (rb.flipX[wn] ? -weaponPos.x[parentEntityIndex] : weaponPos.x[parentEntityIndex]);
    rb.dst.y[wn] = parentPosition.y[parentEntityIndex] + weaponPos.y[parentEntityIndex];
    rb.dst.w[wn] = weaponPos.w[parentEntityIndex];
    rb.dst.h[wn] = weaponPos.h[parentEntityIndex];
    rb.dst.sortY[wn] = rb.dst.sortY[parentRenderIndex];

    float weaponRotate = (float)weapon.frame.src.rotate[parentEntityIndex][wf];
    rb.src.rotate[wn] = rb.flipX[wn] ? -weaponRotate : weaponRotate;
}
