#pragma once
#include "../../structs/equipment/Equipment.h"
#include "../../structs/tilemap/TileMapProperties.h"
#include "GetAnchor.h"
#include "LoadEntityBase.h"
#include "properties/FindTileByType.h"
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
    std::string weaponType = getTileStringProp(tileset, parentEntityTileIndex, "weapon");
    uint32_t weaponIdx = 0;
    bool hasWeapon = !weaponType.empty() && findTileByType(tileset, weaponType.c_str(), weaponIdx);
    if (hasWeapon)
    {
        loadEntityBase(equipmentData.weapon.base, parentEntityIdx, tileset, weaponIdx, props);

        SDL_FRect ammoAnchor = getAnchor(tileset, weaponIdx, "ammoAnchor");
        equipmentData.weapon.ammoAnchor.initialOffX[parentEntityIdx][0] = ammoAnchor.x;
        equipmentData.weapon.ammoAnchor.initialOffY[parentEntityIdx][0] = ammoAnchor.y;
        equipmentData.weapon.ammoAnchor.initialW[parentEntityIdx][0] = ammoAnchor.w;
        equipmentData.weapon.ammoAnchor.initialH[parentEntityIdx][0] = ammoAnchor.h;
        equipmentData.weapon.ammoAnchor.offX[parentEntityIdx][0] = ammoAnchor.x;
        equipmentData.weapon.ammoAnchor.offY[parentEntityIdx][0] = ammoAnchor.y;
        equipmentData.weapon.ammoAnchor.w[parentEntityIdx][0] = ammoAnchor.w;
        equipmentData.weapon.ammoAnchor.h[parentEntityIdx][0] = ammoAnchor.h;
    }

    std::string ammoType = getTileStringProp(tileset, parentEntityTileIndex, "ammo");
    uint32_t ammoIdx = 0;
    bool hasAmmo = !ammoType.empty() && findTileByType(tileset, ammoType.c_str(), ammoIdx);
    equipmentData.weapon.hasAmmo[parentEntityIdx] = hasAmmo;
    if (hasAmmo)
    {
        loadEntityBase(equipmentData.ammo.base, parentEntityIdx, tileset, ammoIdx, props);
        equipmentData.weapon.showAmmo[parentEntityIdx] = true;
    }
}
