#include "IsMarker.h"
#include "properties/GetTileStringProp.h"

bool isMarker(const tmx::Tileset &tileset, uint32_t tileIdx)
{
    return getTileStringProp(tileset, tileIdx, "type") == "marker";
}
