#include "LoadObjects.h"
#include "FindLayer.h"
#include "GetCollision.h"
#include <tmxlite/TileLayer.hpp>

void LoadObjects(Context &ctx, const tmx::Map &map, const tmx::Tileset &tileset)
{
    auto &props = ctx.data.tileMapProps;
    auto &object = ctx.data.object;
    auto &objectTiles = FindLayer(map, "Object")->getLayerAs<tmx::TileLayer>().getTiles();
    object.objectCount = 0;
    for (uint32_t i = 0; i < objectTiles.size(); i++)
    {
        if (objectTiles[i].ID == 0)
            continue;
        uint32_t n = object.objectCount++;
        uint32_t idx = objectTiles[i].ID - props.firstGid;
        object.src.x[n] = idx % props.columns * props.srcTileW;
        object.src.y[n] = idx / props.columns * props.srcTileH;
        object.src.w[n] = props.srcTileW;
        object.src.h[n] = props.srcTileH;
        object.position.x[n] = i % props.mapW * props.dstTileW;
        object.position.y[n] = i / props.mapW * props.dstTileH;
        object.position.w[n] = props.dstTileW;
        object.position.h[n] = props.dstTileH;
        GetCollision(tileset, idx, object.collision.offX[n], object.collision.offY[n], object.collision.w[n], object.collision.h[n]);
    }
}
