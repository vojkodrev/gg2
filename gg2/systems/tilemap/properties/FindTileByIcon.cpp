#include "FindTileByIcon.h"

bool findTileByIcon(
    const tmx::Tileset &tileset,
    const std::string &icon,
    uint32_t &outTileIdx)
{
    for (auto &tile : tileset.getTiles())
    {
        for (auto &prop : tile.properties)
        {
            if (prop.getName() == "icon" && prop.getStringValue() == icon)
            {
                outTileIdx = tile.ID;
                return true;
            }
        }
    }
    return false;
}
