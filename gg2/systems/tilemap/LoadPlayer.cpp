#include "LoadPlayer.h"
#include "FindLayer.h"
#include "properties/FindTileByType.h"
#include "properties/GetTileFloatProp.h"
#include "properties/GetTileIntProp.h"
#include "properties/GetTileStringProp.h"
#include "LoadTileAnimation.h"
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

        std::string weaponType = getTileStringProp(tileset, idx, "weapon");
        uint32_t weaponIdx = 0;
        bool hasWeapon = !weaponType.empty() && findTileByType(tileset, weaponType.c_str(), weaponIdx);
        if (hasWeapon)
        {
            auto &weapon = ctx.data.player.equipment.weapon;
            auto &weaponPos = ctx.data.player.equipment.position;
            weapon.frameCount[0] = 1;
            SDL_Point srcGrid = decodeGridIndex((int)weaponIdx, props.columns);
            weapon.frame.src.x[0][0] = srcGrid.x * props.srcTileW;
            weapon.frame.src.y[0][0] = srcGrid.y * props.srcTileH;
            weapon.frame.src.w[0][0] = props.srcTileW;
            weapon.frame.src.h[0][0] = props.srcTileH;
            weapon.frame.frameDuration[0][0] = 0;

            float scale = getTileFloatProp(tileset, weaponIdx, "scale", 1.0f);
            weaponPos.x[0] = (float)getTileIntProp(tileset, weaponIdx, "x");
            weaponPos.y[0] = (float)getTileIntProp(tileset, weaponIdx, "y");
            weaponPos.w[0] = props.dstTileW * scale;
            weaponPos.h[0] = props.dstTileH * scale;

            float rotate = getTileFloatProp(tileset, weaponIdx, "rotate", 0.0f);
            weapon.frame.src.rotate[0][0] = rotate;

            weapon.frameIndex[0] = 0;
            weapon.animationStartTime[0] = 0;
        }
        break;
    }
}
