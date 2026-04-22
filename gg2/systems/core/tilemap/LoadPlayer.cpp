#include "LoadPlayer.h"
#include "FindLayer.h"
#include "GetCollision.h"
#include <tmxlite/TileLayer.hpp>

void loadPlayer(Context &ctx, const tmx::Map &map, const tmx::Tileset &tileset)
{
    auto &props = ctx.data.tileMapProps;
    auto &playerTiles = findLayer(map, "Player")->getLayerAs<tmx::TileLayer>().getTiles();
    for (int i = 0; i < (int)playerTiles.size(); i++)
    {
        if (playerTiles[i].ID == 0)
            continue;
        uint32_t idx = playerTiles[i].ID - props.firstGid;
        ctx.data.player.srcX = idx % props.columns * props.srcTileW;
        ctx.data.player.srcY = idx / props.columns * props.srcTileH;
        ctx.data.player.srcW = props.srcTileW;
        ctx.data.player.srcH = props.srcTileH;
        ctx.data.player.x = i % props.mapW * props.dstTileW;
        ctx.data.player.y = i / props.mapW * props.dstTileH;
        ctx.data.player.w = props.dstTileW;
        ctx.data.player.h = props.dstTileH;
        getCollision(tileset, idx, ctx.data.player.colOffX, ctx.data.player.colOffY, ctx.data.player.colW, ctx.data.player.colH);
        break;
    }
}
