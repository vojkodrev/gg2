#include "LoadPlayer.h"
#include "FindLayer.h"
#include "LoadEntityBase.h"
#include "LoadEquipment.h"
#include "DecodeGridIndex.h"
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
        loadEntityBase(ctx.data.player, 0, tileset, idx, props);
        SDL_Point grid = decodeGridIndex(i, props.mapW);
        ctx.data.player.base.position.x[0] = grid.x * props.dstTileW;
        ctx.data.player.base.position.y[0] = grid.y * props.dstTileH;

        loadEquipment(ctx.data.player.equipment, 0, tileset, idx, props);
        break;
    }
}
