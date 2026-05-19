#pragma once
#include "../../structs/equipment/Weapon.h"
#include "../../structs/tilemap/TileMapProperties.h"
#include "DecodeGridIndex.h"
#include "properties/FindTileByType.h"
#include "properties/GetTileFloatProp.h"
#include "properties/GetTileIntProp.h"
#include "properties/GetTileStringProp.h"
#include <cstdint>
#include <tmxlite/Tileset.hpp>

template<int N>
inline void loadWeapon(Weapon<N> &weaponData, uint32_t n, const tmx::Tileset &tileset, uint32_t idx, const TileMapProperties &props)
{
    std::string weaponType = getTileStringProp(tileset, idx, "weapon");
    uint32_t weaponIdx = 0;
    bool hasWeapon = !weaponType.empty() && findTileByType(tileset, weaponType.c_str(), weaponIdx);
    if (!hasWeapon)
    {
        weaponData.animation.frameCount[n] = 0;
        return;
    }

    auto &weapon = weaponData.animation;
    auto &weaponPos = weaponData.position;
    weapon.frameCount[n] = 1;
    SDL_Point srcGrid = decodeGridIndex((int)weaponIdx, props.columns);
    weapon.frame.src.x[n][0] = srcGrid.x * props.srcTileW;
    weapon.frame.src.y[n][0] = srcGrid.y * props.srcTileH;
    weapon.frame.src.w[n][0] = props.srcTileW;
    weapon.frame.src.h[n][0] = props.srcTileH;
    weapon.frame.frameDuration[n][0] = 0;

    float scale = getTileFloatProp(tileset, weaponIdx, "scale", 1.0f);
    weaponPos.x[n] = (float)getTileIntProp(tileset, weaponIdx, "x");
    weaponPos.y[n] = (float)getTileIntProp(tileset, weaponIdx, "y");
    weaponPos.w[n] = props.dstTileW * scale;
    weaponPos.h[n] = props.dstTileH * scale;

    float rotate = getTileFloatProp(tileset, weaponIdx, "rotate", 0.0f);
    weapon.frame.src.rotate[n][0] = rotate;

    weapon.frameIndex[n] = 0;
    weapon.animationStartTime[n] = 0;
}
