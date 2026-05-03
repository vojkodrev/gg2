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
        ctx.data.player.src.x[0] = idx % props.columns * props.srcTileW;
        ctx.data.player.src.y[0] = idx / props.columns * props.srcTileH;
        ctx.data.player.src.w[0] = props.srcTileW;
        ctx.data.player.src.h[0] = props.srcTileH;
        ctx.data.player.position.x[0] = i % props.mapW * props.dstTileW;
        ctx.data.player.position.y[0] = i / props.mapW * props.dstTileH;
        ctx.data.player.position.w[0] = props.dstTileW;
        ctx.data.player.position.h[0] = props.dstTileH;
        getCollision(tileset, idx, ctx.data.player.collision.offX[0], ctx.data.player.collision.offY[0], ctx.data.player.collision.w[0], ctx.data.player.collision.h[0]);
        break;
    }
}
