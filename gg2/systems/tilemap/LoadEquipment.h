#pragma once
#include "../../structs/equipment/Equipment.h"
#include "../../structs/tilemap/TileMapProperties.h"
#include "LoadEntityBase.h"
#include "properties/FindTileByType.h"
#include "properties/GetTileStringProp.h"
#include <cstdint>
#include <tmxlite/Tileset.hpp>

template<int N>
inline void loadEquipment(Equipment<N> &equipmentData, uint32_t parentEntityIdx, const tmx::Tileset &tileset, uint32_t parentEntityTileIndex, const TileMapProperties &props)
{
    std::string ammoType = getTileStringProp(tileset, parentEntityTileIndex, "ammo");
    uint32_t ammoIdx = 0;
    bool hasAmmo = !ammoType.empty() && findTileByType(tileset, ammoType.c_str(), ammoIdx);
    if (hasAmmo)
        loadEntityBase(equipmentData.ammo, parentEntityIdx, tileset, ammoIdx, props);

    std::string weaponType = getTileStringProp(tileset, parentEntityTileIndex, "weapon");
    uint32_t weaponIdx = 0;
    bool hasWeapon = !weaponType.empty() && findTileByType(tileset, weaponType.c_str(), weaponIdx);
    if (hasWeapon)
        loadEntityBase(equipmentData.weapon, parentEntityIdx, tileset, weaponIdx, props);
}
