#include "FindTileByType.h"

bool findTileByType(const tmx::Tileset &tileset, const char *type, uint32_t &outTileIdx)
{
    for (auto &tile : tileset.getTiles())
    {
        for (auto &prop : tile.properties)
        {
            if (prop.getName() == "type" && prop.getStringValue() == type)
            {
                outTileIdx = tile.ID;
                return true;
            }
        }
    }
    return false;
}
