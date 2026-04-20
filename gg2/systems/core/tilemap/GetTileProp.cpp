#include "GetTileProp.h"

int GetTileProp(const tmx::Tileset &tileset, uint32_t tileIdx, const std::string &name)
{
    for (auto &tile : tileset.getTiles())
    {
        if (tile.ID != tileIdx)
            continue;
        for (auto &prop : tile.properties)
            if (prop.getName() == name)
                return prop.getIntValue();
    }
    return 0;
}
