#pragma once
#include "../../structs/equipment/Weapon.h"
#include "../../structs/core/Animation.h"
#include "../../structs/core/EntityPosition.h"
#include "../../structs/render/RenderBuffer.h"
#include "../../structs/core/constants/RenderConstants.h"
#include <cstdint>

template<int N>
inline void fillWeaponRenderBuffer(RenderBuffer &rb, const Weapon<N> &weaponData, uint32_t parentEntityIndex, uint32_t parentRenderIndex, uint32_t groupId)
{
    const auto &weapon = weaponData.base.animation;
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
    rb.flipX[wn] = weaponData.base.facing.flipX[parentEntityIndex];

    rb.dst.w[wn] = weaponData.base.position.w[parentEntityIndex];
    rb.dst.h[wn] = weaponData.base.position.h[parentEntityIndex];
    rb.dst.x[wn] = weaponData.base.position.x[parentEntityIndex];
    rb.dst.y[wn] = weaponData.base.position.y[parentEntityIndex];
    rb.dst.sortY[wn] = rb.dst.sortY[parentRenderIndex];

    rb.src.rotate[wn] = weaponData.base.rotation.rotate[parentEntityIndex];
}
