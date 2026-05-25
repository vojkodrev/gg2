#pragma once
#include "../../structs/tilemap/TileMapProperties.h"
#include "DecodeGridIndex.h"
#include "GetAnchor.h"
#include "properties/FindTileByType.h"
#include "properties/GetTileFloatProp.h"
#include "properties/GetTileStringProp.h"
#include <cstdint>
#include <tmxlite/Tileset.hpp>

template<typename EntityData>
inline void loadEntityBase(
    EntityData &entityData,
    uint32_t parentEntityIdx,
    const tmx::Tileset &tileset,
    uint32_t entityTileIdx,
    const TileMapProperties &props)
{
    auto &entity = entityData.animation;
    entity.animationType[parentEntityIdx] = AnimationType::None;
    entity.frameCount[parentEntityIdx] = 1;
    SDL_Point srcGrid = decodeGridIndex((int)entityTileIdx, props.columns);
    entity.frame.src.x[parentEntityIdx][0] = srcGrid.x * props.srcTileW;
    entity.frame.src.y[parentEntityIdx][0] = srcGrid.y * props.srcTileH;
    entity.frame.src.w[parentEntityIdx][0] = props.srcTileW;
    entity.frame.src.h[parentEntityIdx][0] = props.srcTileH;
    entityData.position.initialW[parentEntityIdx] = props.srcTileW;
    entityData.position.initialH[parentEntityIdx] = props.srcTileH;
    entityData.position.w[parentEntityIdx] = entityData.position.initialW[parentEntityIdx];
    entityData.position.h[parentEntityIdx] = entityData.position.initialH[parentEntityIdx];
    entity.frame.frameDuration[parentEntityIdx][0] = 0;

    SDL_FRect anchor = getAnchor(tileset, entityTileIdx, "anchor");
    entity.frame.anchor.initialOffX[parentEntityIdx][0] = anchor.x;
    entity.frame.anchor.initialOffY[parentEntityIdx][0] = anchor.y;
    entity.frame.anchor.initialW[parentEntityIdx][0] = anchor.w;
    entity.frame.anchor.initialH[parentEntityIdx][0] = anchor.h;
    entity.frame.anchor.offX[parentEntityIdx][0] = anchor.x;
    entity.frame.anchor.offY[parentEntityIdx][0] = anchor.y;
    entity.frame.anchor.w[parentEntityIdx][0] = anchor.w;
    entity.frame.anchor.h[parentEntityIdx][0] = anchor.h;

    SDL_FRect col = getAnchor(tileset, entityTileIdx, "collision");
    entity.frame.collision.initialOffX[parentEntityIdx][0] = col.x;
    entity.frame.collision.initialOffY[parentEntityIdx][0] = col.y;
    entity.frame.collision.initialW[parentEntityIdx][0] = col.w;
    entity.frame.collision.initialH[parentEntityIdx][0] = col.h;
    entity.frame.collision.offX[parentEntityIdx][0] = col.x;
    entity.frame.collision.offY[parentEntityIdx][0] = col.y;
    entity.frame.collision.w[parentEntityIdx][0] = col.w;
    entity.frame.collision.h[parentEntityIdx][0] = col.h;

    entityData.scale[parentEntityIdx] = getTileFloatProp(tileset, entityTileIdx, "scale", 1.0f);
    entityData.rotation.initialRotate[parentEntityIdx] = getTileFloatProp(tileset, entityTileIdx, "rotate", 0.0f);
    entityData.rotation.rotate[parentEntityIdx] = entityData.rotation.initialRotate[parentEntityIdx];
    entityData.rotation.initialAngle[parentEntityIdx] = getTileFloatProp(tileset, entityTileIdx, "initialAngle", 0.0f);

    FacingDirection entityFacing = getTileStringProp(tileset, entityTileIdx, "facing") == "left" ? FacingDirection::Left : FacingDirection::Right;
    entityData.facing.facing[parentEntityIdx] = entityFacing;
    entityData.facing.initialFacing[parentEntityIdx] = entityFacing;

    entity.frameIndex[parentEntityIdx] = 0;
    entity.animationStartTime[parentEntityIdx] = 0;
    entity.animationStopTime[parentEntityIdx] = 0;
}
