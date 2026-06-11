#include "LoadObjects.h"
#include "FindLayer.h"
#include "LoadEntityBase.h"
#include "../../utils/groups/AllocGroup.h"
#include <tmxlite/TileLayer.hpp>

void loadObjects(Context &ctx, const tmx::Map &map, const tmx::Tileset &tileset)
{
    auto &props = ctx.data.tileMapProps;
    auto &object = ctx.data.object;
    auto &objectTiles = findLayer(map, "Object")->getLayerAs<tmx::TileLayer>().getTiles();
    object.objectCount = 0;
    for (uint32_t i = 0; i < objectTiles.size(); i++)
    {
        if (objectTiles[i].ID == 0)
            continue;
        uint32_t n = object.objectCount++;
        uint32_t idx = objectTiles[i].ID - props.firstGid;
        loadEntityBase(object.base, n, tileset, idx, props, i);
        object.groupId[n] = allocGroup(ctx.data.groups);
    }
}
