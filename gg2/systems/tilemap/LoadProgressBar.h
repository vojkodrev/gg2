#pragma once
#include "../../structs/tilemap/TileMapProperties.h"
#include "../../structs/core/constants/ZIndexConstants.h"
#include "../../structs/ui/ProgressBar.h"
#include "LoadEntityBase.h"
#include "properties/FindTileByType.h"
#include "properties/GetTileStringProp.h"
#include <cstdint>
#include <string>
#include <tmxlite/Tileset.hpp>

template<int N>
inline void loadProgressBar(
    ProgressBar<N> &progressBar,
    uint32_t parentEntityIndex,
    const tmx::Tileset &tileset,
    uint32_t parentEntityTileIndex,
    const TileMapProperties &props,
    const char *propertyName)
{
    const std::string progressBarType =
        getTileStringProp(tileset, parentEntityTileIndex, propertyName);
    uint32_t progressBarTileIndex = 0;
    const bool hasProgressBar = !progressBarType.empty() &&
        findTileByType(
            tileset,
            progressBarType,
            progressBarTileIndex);
    progressBar.show[parentEntityIndex] = false;
    progressBar.dirty[parentEntityIndex] = false;
    progressBar.zIndex[parentEntityIndex] = HP_MANA_BAR_Z_INDEX;
    if (!hasProgressBar)
        return;

    loadEntityBase(
        progressBar.base,
        parentEntityIndex,
        tileset,
        progressBarTileIndex,
        props);
}
