#include "GetTileFloatProp.h"

float getTileFloatProp(const tmx::Tileset &tileset, uint32_t tileIdx, const std::string &name, float defaultVal)
{
    for (auto &tile : tileset.getTiles())
    {
        if (tile.ID != tileIdx)
            continue;
        for (auto &prop : tile.properties)
            if (prop.getName() == name)
                return prop.getFloatValue();
    }
    return defaultVal;
}
