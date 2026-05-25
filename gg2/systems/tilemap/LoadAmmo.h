#pragma once
#include "../../structs/equipment/Ammo.h"
#include "../../structs/tilemap/TileMapProperties.h"
#include "DecodeGridIndex.h"
#include "GetAnchor.h"
#include "properties/FindTileByType.h"
#include "properties/GetTileFloatProp.h"
#include "properties/GetTileStringProp.h"
#include <cstdint>
#include <tmxlite/Tileset.hpp>

template<int N>
inline void loadAmmo(Ammo<N> &ammoData, uint32_t parentEntityIndex, const tmx::Tileset &tileset, uint32_t parentEntityTileIndex, const TileMapProperties &props)
{
    std::string ammoType = getTileStringProp(tileset, parentEntityTileIndex, "ammo");
    uint32_t ammoIdx = 0;
    bool hasAmmo = !ammoType.empty() && findTileByType(tileset, ammoType.c_str(), ammoIdx);
    if (!hasAmmo)
    {
        ammoData.animation.animationType[parentEntityIndex] = AnimationType::None;
        ammoData.animation.frameCount[parentEntityIndex] = 0;
        return;
    }

    auto &ammo = ammoData.animation;
    ammo.animationType[parentEntityIndex] = AnimationType::None;
    ammo.frameCount[parentEntityIndex] = 1;
    SDL_Point srcGrid = decodeGridIndex((int)ammoIdx, props.columns);
    ammo.frame.src.x[parentEntityIndex][0] = srcGrid.x * props.srcTileW;
    ammo.frame.src.y[parentEntityIndex][0] = srcGrid.y * props.srcTileH;
    ammo.frame.src.w[parentEntityIndex][0] = props.srcTileW;
    ammo.frame.src.h[parentEntityIndex][0] = props.srcTileH;
    ammoData.position.initialW[parentEntityIndex] = props.srcTileW;
    ammoData.position.initialH[parentEntityIndex] = props.srcTileH;
    ammoData.position.w[parentEntityIndex] = ammoData.position.initialW[parentEntityIndex];
    ammoData.position.h[parentEntityIndex] = ammoData.position.initialH[parentEntityIndex];
    ammo.frame.frameDuration[parentEntityIndex][0] = 0;
    SDL_FRect anchor = getAnchor(tileset, ammoIdx, "anchor");
    ammo.frame.anchor.initialOffX[parentEntityIndex][0] = anchor.x;
    ammo.frame.anchor.initialOffY[parentEntityIndex][0] = anchor.y;
    ammo.frame.anchor.initialW[parentEntityIndex][0] = anchor.w;
    ammo.frame.anchor.initialH[parentEntityIndex][0] = anchor.h;
    ammo.frame.anchor.offX[parentEntityIndex][0] = anchor.x;
    ammo.frame.anchor.offY[parentEntityIndex][0] = anchor.y;
    ammo.frame.anchor.w[parentEntityIndex][0] = anchor.w;
    ammo.frame.anchor.h[parentEntityIndex][0] = anchor.h;
    SDL_FRect col = getAnchor(tileset, ammoIdx, "collision");
    ammo.frame.collision.initialOffX[parentEntityIndex][0] = col.x;
    ammo.frame.collision.initialOffY[parentEntityIndex][0] = col.y;
    ammo.frame.collision.initialW[parentEntityIndex][0] = col.w;
    ammo.frame.collision.initialH[parentEntityIndex][0] = col.h;
    ammo.frame.collision.offX[parentEntityIndex][0] = col.x;
    ammo.frame.collision.offY[parentEntityIndex][0] = col.y;
    ammo.frame.collision.w[parentEntityIndex][0] = col.w;
    ammo.frame.collision.h[parentEntityIndex][0] = col.h;

    float scale = getTileFloatProp(tileset, ammoIdx, "scale", 1.0f);
    ammoData.scale[parentEntityIndex] = scale;

    ammoData.rotation.initialRotate[parentEntityIndex] = getTileFloatProp(tileset, ammoIdx, "rotate", 0.0f);
    ammoData.rotation.rotate[parentEntityIndex] = ammoData.rotation.initialRotate[parentEntityIndex];
    ammoData.rotation.initialAngle[parentEntityIndex] = getTileFloatProp(tileset, ammoIdx, "initialAngle", 0.0f);

    FacingDirection ammoFacing = getTileStringProp(tileset, ammoIdx, "facing") == "left" ? FacingDirection::Left : FacingDirection::Right;
    ammoData.facing.facing[parentEntityIndex] = ammoFacing;
    ammoData.facing.initialFacing[parentEntityIndex] = ammoFacing;

    ammo.frameIndex[parentEntityIndex] = 0;
    ammo.animationStartTime[parentEntityIndex] = 0;
    ammo.animationStopTime[parentEntityIndex] = 0;
}
