#pragma once
#include "RotateEntityBase.h"
#include "../../../structs/equipment/Equipment.h"
#include "../../../utils/rect/RotateRectCenter.h"
#include <cstdint>

template<int N>
inline void rotateEquipment(
    Equipment<N> &equipment,
    uint32_t entityIndex,
    bool rotateWeapon,
    bool rotateAmmo,
    bool useRotationAnimationStart = false)
{
    auto &weapon = equipment.weapon;
    const WeaponType weaponType = weapon.type[entityIndex];

    if (rotateWeapon)
    {
        rotateEntityBase(
            weapon.base,
            entityIndex,
            useRotationAnimationStart);

        if (weaponType == WeaponType::Ranged ||
            weaponType == WeaponType::Magic)
        {
            auto &anchor = weaponType == WeaponType::Ranged
                ? weapon.ranged.ammoAnchor
                : weapon.magic.spellAnchor;
            const float weaponCenterX =
                weapon.base.position.w[entityIndex] * 0.5f;
            const float weaponCenterY =
                weapon.base.position.h[entityIndex] * 0.5f;
            const float weaponRotation =
                weapon.base.rotation.rotate[entityIndex];

            for (int frameIndex = 0;
                frameIndex < weapon.base.animation.frameCount[entityIndex];
                frameIndex++)
                rotateRectCenter(
                    anchor.offX[entityIndex][frameIndex][0],
                    anchor.offY[entityIndex][frameIndex][0],
                    anchor.w[entityIndex][frameIndex][0],
                    anchor.h[entityIndex][frameIndex][0],
                    weaponCenterX,
                    weaponCenterY,
                    weaponRotation);
        }
    }

    if (rotateAmmo)
        rotateEntityBase(equipment.ammo.base, entityIndex);
}
