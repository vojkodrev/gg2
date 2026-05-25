#pragma once
#include "../../structs/tilemap/TileMapProperties.h"
#include "LoadTileAnimation.h"
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
    loadTileAnimation(entityData.animation, parentEntityIdx, tileset, entityTileIdx, props);

    entityData.position.initialW[parentEntityIdx] = props.srcTileW;
    entityData.position.initialH[parentEntityIdx] = props.srcTileH;
    entityData.position.w[parentEntityIdx] = entityData.position.initialW[parentEntityIdx];
    entityData.position.h[parentEntityIdx] = entityData.position.initialH[parentEntityIdx];

    entityData.scale[parentEntityIdx] = getTileFloatProp(tileset, entityTileIdx, "scale", 1.0f);
    entityData.rotation.initialRotate[parentEntityIdx] = getTileFloatProp(tileset, entityTileIdx, "rotate", 0.0f);
    entityData.rotation.rotate[parentEntityIdx] = entityData.rotation.initialRotate[parentEntityIdx];
    entityData.rotation.initialAngle[parentEntityIdx] = getTileFloatProp(tileset, entityTileIdx, "initialAngle", 0.0f);

    FacingDirection entityFacing = getTileStringProp(tileset, entityTileIdx, "facing") == "left" ? FacingDirection::Left : FacingDirection::Right;
    entityData.facing.facing[parentEntityIdx] = entityFacing;
    entityData.facing.initialFacing[parentEntityIdx] = entityFacing;
}
