#include "IsMarker.h"

bool IsMarker(const tmx::Tileset &tileset, uint32_t tileIdx)
{
    for (auto &tile : tileset.getTiles())
    {
        if (tile.ID != tileIdx)
            continue;
        for (auto &prop : tile.properties)
            if (prop.getName() == "type" && prop.getStringValue() == "marker")
                return true;
        return false;
    }
    return false;
}
