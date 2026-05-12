#include "GetTileProp.h"

int getTileProp(const tmx::Tileset &tileset, uint32_t tileIdx, const std::string &name)
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

std::string getTileStringProp(const tmx::Tileset &tileset, uint32_t tileIdx, const std::string &name)
{
    for (auto &tile : tileset.getTiles())
    {
        if (tile.ID != tileIdx)
            continue;
        for (auto &prop : tile.properties)
            if (prop.getName() == name)
                return prop.getStringValue();
    }
    return "";
}

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
