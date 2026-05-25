#pragma once
#include "../../structs/equipment/Equipment.h"
#include "../../structs/tilemap/TileMapProperties.h"
#include "LoadAmmo.h"
#include "LoadWeapon.h"
#include <cstdint>
#include <tmxlite/Tileset.hpp>

template<int N>
inline void loadEquipment(Equipment<N> &equipmentData, uint32_t parentEntityIndex, const tmx::Tileset &tileset, uint32_t parentEntityTileIndex, const TileMapProperties &props)
{
    loadAmmo(equipmentData.ammo, parentEntityIndex, tileset, parentEntityTileIndex, props);
    loadWeapon(equipmentData.weapon, parentEntityIndex, tileset, parentEntityTileIndex, props);
}
