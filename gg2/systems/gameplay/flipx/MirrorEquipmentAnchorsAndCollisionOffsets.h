#pragma once
#include "MirrorAnchorOffsetX.h"
#include "MirrorEntityAnchorsAndCollisionOffsets.h"
#include "../../../structs/equipment/Equipment.h"
#include <cstdint>

template<int N>
inline void mirrorEquipmentAnchorsAndCollisionOffsets(
    Equipment<N> &equipment,
    uint32_t entityIndex,
    bool mirrorWeapon,
    bool mirrorAmmo)
{
    auto &weapon = equipment.weapon;
    const WeaponType weaponType = weapon.type[entityIndex];
    const float weaponW = weapon.base.position.w[entityIndex];
    if (mirrorWeapon)
    {
        mirrorEntityAnchorsAndCollisionOffsets(weapon.base, entityIndex);

        for (int frameIndex = 0;
            frameIndex < weapon.base.animation.frameCount[entityIndex];
            frameIndex++)
        {
            if (weaponType == WeaponType::Ranged)
                mirrorAnchorOffsetX(
                    weapon.ranged.ammoAnchor,
                    weaponW,
                    entityIndex,
                    frameIndex,
                    0);
            else if (weaponType == WeaponType::Magic)
                mirrorAnchorOffsetX(
                    weapon.magic.spellAnchor,
                    weaponW,
                    entityIndex,
                    frameIndex,
                    0);
        }
    }

    if (mirrorAmmo)
        mirrorEntityAnchorsAndCollisionOffsets(
            equipment.ammo.base,
            entityIndex);
}
