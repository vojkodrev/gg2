#include "LoadGround.h"
#include "FindLayer.h"
#include "GetTileIndex.h"
#include "DecodeGridIndex.h"
#include <tmxlite/TileLayer.hpp>

void loadGround(Context &ctx, const tmx::Map &map, const tmx::Tileset &tileset)
{
    auto &props = ctx.data.tileMapProps;
    auto &tileMap = ctx.data.tileMap;
    props.srcTileW = tileset.getTileSize().x;
    props.srcTileH = tileset.getTileSize().y;
    props.tilesetW = tileset.getColumnCount();
    props.mapW = map.getTileCount().x;
    props.dstTileW = map.getTileSize().x;
    props.dstTileH = map.getTileSize().y;
    props.firstGid = tileset.getFirstGID();

    auto &srcTiles = findLayer(map, "Ground")->getLayerAs<tmx::TileLayer>().getTiles();
    tileMap.tileCount = 0;
    for (int i = 0; i < (int)srcTiles.size(); i++)
    {
        uint32_t gid = srcTiles[i].ID;
        if (gid == 0)
            continue;
        uint32_t n = tileMap.tileCount++;
        uint32_t idx = getTileIndex(gid, props);
        tileMap.tiles.srcX[n] = idx % props.tilesetW * props.srcTileW;
        tileMap.tiles.srcY[n] = idx / props.tilesetW * props.srcTileH;
        SDL_Point grid = decodeGridIndex(i, props.mapW);
        tileMap.tiles.dstX[n] = grid.x * props.dstTileW;
        tileMap.tiles.dstY[n] = grid.y * props.dstTileH;
    }
}
