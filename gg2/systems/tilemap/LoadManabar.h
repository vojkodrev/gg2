#pragma once
#include "../../structs/tilemap/TileMapProperties.h"
#include "../../structs/core/constants/ZIndexConstants.h"
#include "../../structs/ui/Manabar.h"
#include "LoadEntityBase.h"
#include "properties/FindTileByType.h"
#include "properties/GetTileStringProp.h"
#include <cstdint>
#include <tmxlite/Tileset.hpp>

template<int N>
inline void loadManabar(
    Manabar<N> &manabarData,
    uint32_t parentEntityIdx,
    const tmx::Tileset &tileset,
    uint32_t parentEntityTileIndex,
    const TileMapProperties &props)
{
    std::string manabarType = getTileStringProp(tileset, parentEntityTileIndex, "manabar");
    uint32_t manabarIdx = 0;
    bool hasManabar = !manabarType.empty() && findTileByType(tileset, manabarType.c_str(), manabarIdx);
    manabarData.show[parentEntityIdx] = false;
    manabarData.dirty[parentEntityIdx] = false;
    manabarData.zIndex[parentEntityIdx] = HP_MANA_BAR_Z_INDEX;
    if (!hasManabar)
        return;

    loadEntityBase(manabarData.base, parentEntityIdx, tileset, manabarIdx, props);
}
