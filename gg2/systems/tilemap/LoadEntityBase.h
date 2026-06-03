#pragma once
#include "../../structs/core/EntityBase.h"
#include "../../structs/tilemap/TileMapProperties.h"
#include "DecodeGridIndex.h"
#include "IsMarker.h"
#include "LoadTileAnimation.h"
#include "properties/GetTileFloatProp.h"
#include "properties/GetTileIntProp.h"
#include "properties/GetTileStringProp.h"
#include <cstdint>
#include <tmxlite/Tileset.hpp>

template<int N>
inline void loadEntityBase(
    EntityBase<N> &entityData,
    uint32_t parentEntityIdx,
    const tmx::Tileset &tileset,
    uint32_t entityTileIdx,
    const TileMapProperties &props,
    uint32_t tileArrayIdx = UINT32_MAX)
{
    bool marker = tileArrayIdx != UINT32_MAX && isMarker(tileset, entityTileIdx);
    if (marker)
    {
        entityData.animation.frame.src.x[parentEntityIdx][0] = getTileIntProp(tileset, entityTileIdx, "x");
        entityData.animation.frame.src.y[parentEntityIdx][0] = getTileIntProp(tileset, entityTileIdx, "y");
        entityData.animation.frame.src.w[parentEntityIdx][0] = getTileIntProp(tileset, entityTileIdx, "w");
        entityData.animation.frame.src.h[parentEntityIdx][0] = getTileIntProp(tileset, entityTileIdx, "h");
        float colOffX = (float)getTileIntProp(tileset, entityTileIdx, "colOffX");
        float colOffY = (float)getTileIntProp(tileset, entityTileIdx, "colOffY");
        float colW = (float)getTileIntProp(tileset, entityTileIdx, "colW");
        float colH = (float)getTileIntProp(tileset, entityTileIdx, "colH");
        float w = (float)getTileIntProp(tileset, entityTileIdx, "w");
        float h = (float)getTileIntProp(tileset, entityTileIdx, "h");
        SDL_Point grid = decodeGridIndex((int)tileArrayIdx, props.mapW);
        float gridX = (float)(grid.x * props.dstTileW);
        float gridY = (float)(grid.y * props.dstTileH);

        entityData.position.x[parentEntityIdx] = gridX + (props.dstTileW - colW) / 2.0f - colOffX;
        entityData.position.y[parentEntityIdx] = gridY + props.dstTileH - colOffY - colH;
        entityData.position.initialW[parentEntityIdx] = w;
        entityData.position.initialH[parentEntityIdx] = h;
        entityData.position.w[parentEntityIdx] = entityData.position.initialW[parentEntityIdx];
        entityData.position.h[parentEntityIdx] = entityData.position.initialH[parentEntityIdx];
        entityData.animation.frame.collision.initialOffX[parentEntityIdx][0] = colOffX;
        entityData.animation.frame.collision.initialOffY[parentEntityIdx][0] = colOffY;
        entityData.animation.frame.collision.initialW[parentEntityIdx][0] = colW;
        entityData.animation.frame.collision.initialH[parentEntityIdx][0] = colH;
        entityData.animation.frame.collision.offX[parentEntityIdx][0] = colOffX;
        entityData.animation.frame.collision.offY[parentEntityIdx][0] = colOffY;
        entityData.animation.frame.collision.w[parentEntityIdx][0] = colW;
        entityData.animation.frame.collision.h[parentEntityIdx][0] = colH;
        entityData.animation.animationType[parentEntityIdx] = AnimationType::None;
        entityData.animation.frameCount[parentEntityIdx] = 1;
        entityData.animation.frame.frameDuration[parentEntityIdx][0] = 0;
        entityData.animation.frameIndex[parentEntityIdx] = 0;
        entityData.animation.animationStartTime[parentEntityIdx] = 0;
        entityData.animation.animationStopTime[parentEntityIdx] = 0;
    }
    else
    {
        loadTileAnimation(entityData.animation, parentEntityIdx, tileset, entityTileIdx, props);
        if (tileArrayIdx != UINT32_MAX)
        {
            SDL_Point grid = decodeGridIndex((int)tileArrayIdx, props.mapW);
            entityData.position.x[parentEntityIdx] = grid.x * props.dstTileW;
            entityData.position.y[parentEntityIdx] = grid.y * props.dstTileH;
        }
        entityData.position.initialW[parentEntityIdx] = props.srcTileW;
        entityData.position.initialH[parentEntityIdx] = props.srcTileH;
        entityData.position.w[parentEntityIdx] = entityData.position.initialW[parentEntityIdx];
        entityData.position.h[parentEntityIdx] = entityData.position.initialH[parentEntityIdx];
    }

    entityData.scale[parentEntityIdx] = getTileFloatProp(tileset, entityTileIdx, "scale", 1.0f);
    entityData.rotation.initialRotate[parentEntityIdx] = getTileFloatProp(tileset, entityTileIdx, "rotate", 0.0f);
    entityData.rotation.rotate[parentEntityIdx] = entityData.rotation.initialRotate[parentEntityIdx];
    entityData.rotation.initialAngle[parentEntityIdx] = getTileFloatProp(tileset, entityTileIdx, "initialAngle", 0.0f);

    FacingDirection entityFacing = getTileStringProp(tileset, entityTileIdx, "facing") == "left" ? FacingDirection::Left : FacingDirection::Right;
    entityData.facing.facing[parentEntityIdx] = entityFacing;
    entityData.facing.initialFacing[parentEntityIdx] = entityFacing;
    entityData.facing.dirty[parentEntityIdx] = true;
}
