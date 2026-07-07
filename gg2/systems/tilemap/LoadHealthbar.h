#pragma once
#include "../../structs/tilemap/TileMapProperties.h"
#include "../../structs/ui/Healthbar.h"
#include "LoadEntityBase.h"
#include "properties/FindTileByType.h"
#include "properties/GetTileStringProp.h"
#include <cstdint>
#include <tmxlite/Tileset.hpp>

template<int N>
inline void loadHealthbar(
    Healthbar<N> &healthbarData,
    uint32_t parentEntityIdx,
    const tmx::Tileset &tileset,
    uint32_t parentEntityTileIndex,
    const TileMapProperties &props)
{
    std::string healthbarType = getTileStringProp(tileset, parentEntityTileIndex, "healthbar");
    uint32_t healthbarIdx = 0;
    bool hasHealthbar = !healthbarType.empty() && findTileByType(tileset, healthbarType.c_str(), healthbarIdx);
    healthbarData.show[parentEntityIdx] = false;
    healthbarData.dirty[parentEntityIdx] = false;
    if (!hasHealthbar)
        return;

    loadEntityBase(healthbarData.base, parentEntityIdx, tileset, healthbarIdx, props);
}
