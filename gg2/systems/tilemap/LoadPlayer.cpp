#include "LoadPlayer.h"
#include "FindLayer.h"
#include "properties/GetTileStringProp.h"
#include "LoadTileAnimation.h"
#include "LoadWeapon.h"
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
        loadTileAnimation(ctx.data.player.animation, 0, tileset, idx, props);
        SDL_Point grid = decodeGridIndex(i, props.mapW);
        ctx.data.player.position.x[0] = grid.x * props.dstTileW;
        ctx.data.player.position.y[0] = grid.y * props.dstTileH;
        ctx.data.player.position.w[0] = props.dstTileW;
        ctx.data.player.position.h[0] = props.dstTileH;
        FacingDirection f = getTileStringProp(tileset, idx, "facing") == "right" ? FacingDirection::Right : FacingDirection::Left;
        ctx.data.player.facing.facing[0] = f;
        ctx.data.player.facing.initialFacing[0] = f;

        loadWeapon(ctx.data.player.equipment.weapon, 0, tileset, idx, props);
        break;
    }
}
