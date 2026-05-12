#include "LoadPlayer.h"
#include "FindLayer.h"
#include "properties/FindTileByType.h"
#include "properties/GetTilePropInt.h"
#include "properties/GetTileStringProp.h"
#include "LoadTileAnimation.h"
#include "DecodeGridIndex.h"
#include <tmxlite/TileLayer.hpp>

void loadPlayer(Context &ctx, const tmx::Map &map, const tmx::Tileset &tileset)
{
    auto &props = ctx.data.tileMapProps;
    auto &playerTiles = findLayer(map, "Player")->getLayerAs<tmx::TileLayer>().getTiles();

    uint32_t bowIdx = 0;
    bool hasBow = findTileByType(tileset, "bow1", bowIdx);

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

        if (hasBow)
        {
            auto &weapon = ctx.data.player.equipment.weapon;
            weapon.frameCount[0] = 1;
            SDL_Point srcGrid = decodeGridIndex((int)bowIdx, props.columns);
            weapon.frame.src.x[0][0] = srcGrid.x * props.srcTileW;
            weapon.frame.src.y[0][0] = srcGrid.y * props.srcTileH;
            weapon.frame.src.w[0][0] = props.srcTileW;
            weapon.frame.src.h[0][0] = props.srcTileH;
            weapon.frame.frameDuration[0][0] = 0;

            uint32_t srcAngle = (uint32_t)getTileProp(tileset, bowIdx, "angle");
            weapon.frame.src.angle[0][0] = (srcAngle + 360 - 135) % 360;

            weapon.frameIndex[0] = 0;
            weapon.animationStartTime[0] = 0;
        }
        break;
    }
}
