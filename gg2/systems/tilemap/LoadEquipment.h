#pragma once
#include "../../structs/equipment/Equipment.h"
#include "../../structs/equipment/WeaponType.h"
#include "../../structs/tilemap/TileMapProperties.h"
#include "ParseWeaponType.h"
#include "GetAnchor.h"
#include "LoadEntityBase.h"
#include "properties/FindTileByType.h"
#include "properties/GetTileFloatProp.h"
#include "properties/GetTileStringProp.h"
#include <cstdint>
#include <tmxlite/Tileset.hpp>

template<int N>
inline void loadEquipment(
    Equipment<N> &equipmentData, 
    uint32_t parentEntityIdx, 
    const tmx::Tileset &tileset, 
    uint32_t parentEntityTileIndex, 
    const TileMapProperties &props)
{
    std::string weaponAssetType = getTileStringProp(tileset, parentEntityTileIndex, "weapon");
    uint32_t weaponIdx = 0;
    bool hasWeapon = !weaponAssetType.empty() && findTileByType(tileset, weaponAssetType.c_str(), weaponIdx);
    equipmentData.weapon.type[parentEntityIdx] = WeaponType::Melee;
    equipmentData.weapon.showAmmo[parentEntityIdx] = false;
    equipmentData.weapon.ammoAnchor.hasAnchor[parentEntityIdx][0] = false;
    if (hasWeapon && parseWeaponType(weaponAssetType, equipmentData.weapon.type[parentEntityIdx]))
    {
        loadEntityBase(equipmentData.weapon.base, parentEntityIdx, tileset, weaponIdx, props);

        auto &weaponBase = equipmentData.weapon.base;
        weaponBase.scale.value[parentEntityIdx] = getTileFloatProp(
            tileset,
            parentEntityTileIndex,
            "weaponScale",
            weaponBase.scale.value[parentEntityIdx]);
        weaponBase.position.w[parentEntityIdx] =
            weaponBase.position.initialW[parentEntityIdx] * weaponBase.scale.value[parentEntityIdx];
        weaponBase.position.h[parentEntityIdx] =
            weaponBase.position.initialH[parentEntityIdx] * weaponBase.scale.value[parentEntityIdx];

        SDL_FRect ammoAnchor;
        equipmentData.weapon.ammoAnchor.hasAnchor[parentEntityIdx][0] =
            getAnchor(tileset, weaponIdx, "ammoAnchor", ammoAnchor);
        equipmentData.weapon.ammoAnchor.initialOffX[parentEntityIdx][0] = ammoAnchor.x;
        equipmentData.weapon.ammoAnchor.initialOffY[parentEntityIdx][0] = ammoAnchor.y;
        equipmentData.weapon.ammoAnchor.initialW[parentEntityIdx][0] = ammoAnchor.w;
        equipmentData.weapon.ammoAnchor.initialH[parentEntityIdx][0] = ammoAnchor.h;
        equipmentData.weapon.ammoAnchor.offX[parentEntityIdx][0] = ammoAnchor.x;
        equipmentData.weapon.ammoAnchor.offY[parentEntityIdx][0] = ammoAnchor.y;
        equipmentData.weapon.ammoAnchor.w[parentEntityIdx][0] =
            equipmentData.weapon.ammoAnchor.initialW[parentEntityIdx][0] * equipmentData.weapon.base.scale.value[parentEntityIdx];
        equipmentData.weapon.ammoAnchor.h[parentEntityIdx][0] =
            equipmentData.weapon.ammoAnchor.initialH[parentEntityIdx][0] * equipmentData.weapon.base.scale.value[parentEntityIdx];
    }

    std::string ammoType = getTileStringProp(tileset, parentEntityTileIndex, "ammo");
    uint32_t ammoIdx = 0;
    bool hasAmmo = !ammoType.empty() && findTileByType(tileset, ammoType.c_str(), ammoIdx);
    if (hasWeapon && equipmentData.weapon.type[parentEntityIdx] == WeaponType::Ranged)
    {
        if (!hasAmmo)
            return;
        loadEntityBase(equipmentData.ammo.base, parentEntityIdx, tileset, ammoIdx, props);
        equipmentData.weapon.showAmmo[parentEntityIdx] = true;
    }
}
