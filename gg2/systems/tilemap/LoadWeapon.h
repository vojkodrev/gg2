#pragma once
#include "../../structs/equipment/Weapon.h"
#include "../../structs/tilemap/TileMapProperties.h"
#include "DecodeGridIndex.h"
#include "GetAnchor.h"
#include "properties/FindTileByType.h"
#include "properties/GetTileFloatProp.h"
#include "properties/GetTileStringProp.h"
#include <cstdint>
#include <tmxlite/Tileset.hpp>

template<int N>
inline void loadWeapon(Weapon<N> &weaponData, uint32_t parentEntityIndex, const tmx::Tileset &tileset, uint32_t parentEntityTileIndex, const TileMapProperties &props)
{
    std::string weaponType = getTileStringProp(tileset, parentEntityTileIndex, "weapon");
    uint32_t weaponIdx = 0;
    bool hasWeapon = !weaponType.empty() && findTileByType(tileset, weaponType.c_str(), weaponIdx);
    if (!hasWeapon)
    {
        weaponData.animation.animationType[parentEntityIndex] = AnimationType::None;
        weaponData.animation.frameCount[parentEntityIndex] = 0;
        return;
    }

    auto &weapon = weaponData.animation;
    weapon.animationType[parentEntityIndex] = AnimationType::None;
    weapon.frameCount[parentEntityIndex] = 1;
    SDL_Point srcGrid = decodeGridIndex((int)weaponIdx, props.columns);
    weapon.frame.src.x[parentEntityIndex][0] = srcGrid.x * props.srcTileW;
    weapon.frame.src.y[parentEntityIndex][0] = srcGrid.y * props.srcTileH;
    weapon.frame.src.w[parentEntityIndex][0] = props.srcTileW;
    weapon.frame.src.h[parentEntityIndex][0] = props.srcTileH;
    weapon.frame.frameDuration[parentEntityIndex][0] = 0;
    SDL_FRect anchor = getAnchor(tileset, weaponIdx, "anchor");
    weapon.frame.anchor.offX[parentEntityIndex][0] = anchor.x;
    weapon.frame.anchor.offY[parentEntityIndex][0] = anchor.y;
    weapon.frame.anchor.w[parentEntityIndex][0] = anchor.w;
    weapon.frame.anchor.h[parentEntityIndex][0] = anchor.h;
    SDL_FRect col = getAnchor(tileset, weaponIdx, "collision");
    weapon.frame.collision.offX[parentEntityIndex][0] = col.x;
    weapon.frame.collision.offY[parentEntityIndex][0] = col.y;
    weapon.frame.collision.w[parentEntityIndex][0] = col.w;
    weapon.frame.collision.h[parentEntityIndex][0] = col.h;

    float scale = getTileFloatProp(tileset, weaponIdx, "scale", 1.0f);
    weaponData.scale[parentEntityIndex] = scale;

    float rotate = getTileFloatProp(tileset, weaponIdx, "rotate", 0.0f);
    weapon.frame.src.rotate[parentEntityIndex][0] = rotate;
    weapon.frame.src.initialAngle[parentEntityIndex][0] = getTileFloatProp(tileset, weaponIdx, "initialAngle", 0.0f);

    FacingDirection weaponFacing = getTileStringProp(tileset, weaponIdx, "facing") == "left" ? FacingDirection::Left : FacingDirection::Right;
    weaponData.facing.facing[parentEntityIndex] = weaponFacing;
    weaponData.facing.initialFacing[parentEntityIndex] = weaponFacing;

    weapon.frameIndex[parentEntityIndex] = 0;
    weapon.animationStartTime[parentEntityIndex] = 0;
    weapon.animationStopTime[parentEntityIndex] = 0;
}
