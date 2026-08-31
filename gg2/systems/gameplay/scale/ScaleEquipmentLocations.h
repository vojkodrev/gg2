#pragma once
#include "ScaleAnchorLocation.h"
#include "ScaleEntityBaseLocations.h"
#include "../../../structs/equipment/Equipment.h"
#include <cstdint>

template<int N>
inline void scaleEquipmentLocations(
    Equipment<N> &equipment,
    uint32_t entityIndex,
    bool scaleWeapon,
    bool scaleAmmo)
{
    auto &weapon = equipment.weapon;
    const WeaponType weaponType = weapon.type[entityIndex];

    if (scaleWeapon)
    {
        scaleEntityBaseLocations(weapon.base, entityIndex);

        if (weaponType == WeaponType::Ranged ||
            weaponType == WeaponType::Magic)
        {
            auto &anchor = weaponType == WeaponType::Ranged
                ? weapon.ranged.ammoAnchor
                : weapon.magic.spellAnchor;
            const float weaponScale = weapon.base.scale.value[entityIndex];

            for (int frameIndex = 0;
                frameIndex < weapon.base.animation.frameCount[entityIndex];
                frameIndex++)
                scaleAnchorLocation(
                    anchor,
                    weaponScale,
                    entityIndex,
                    frameIndex,
                    0);
        }
    }

    if (scaleAmmo)
        scaleEntityBaseLocations(equipment.ammo.base, entityIndex);
}
