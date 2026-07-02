#pragma once
#include "../../structs/core/EntityBase.h"
#include "../../structs/core/constants/TintConstants.h"
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
    uint32_t entityIdx,
    const tmx::Tileset &tileset,
    uint32_t entityTileIdx,
    const TileMapProperties &props,
    uint32_t tileArrayIdx = UINT32_MAX)
{
    entityData.scale.value[entityIdx] = getTileFloatProp(tileset, entityTileIdx, "scale", 1.0f);

    bool marker = tileArrayIdx != UINT32_MAX && isMarker(tileset, entityTileIdx);
    if (marker)
    {
        entityData.animation.frame.src.x[entityIdx][0] = getTileIntProp(tileset, entityTileIdx, "x");
        entityData.animation.frame.src.y[entityIdx][0] = getTileIntProp(tileset, entityTileIdx, "y");
        entityData.animation.frame.src.w[entityIdx][0] = getTileIntProp(tileset, entityTileIdx, "w");
        entityData.animation.frame.src.h[entityIdx][0] = getTileIntProp(tileset, entityTileIdx, "h");
        float colOffX = (float)getTileIntProp(tileset, entityTileIdx, "colOffX");
        float colOffY = (float)getTileIntProp(tileset, entityTileIdx, "colOffY");
        float colW = (float)getTileIntProp(tileset, entityTileIdx, "colW");
        float colH = (float)getTileIntProp(tileset, entityTileIdx, "colH");
        float w = (float)getTileIntProp(tileset, entityTileIdx, "w");
        float h = (float)getTileIntProp(tileset, entityTileIdx, "h");
        SDL_Point grid = decodeGridIndex((int)tileArrayIdx, props.mapW);
        float gridX = (float)(grid.x * props.dstTileW);
        float gridY = (float)(grid.y * props.dstTileH);

        entityData.position.x[entityIdx] = gridX + (props.dstTileW - colW) / 2.0f - colOffX;
        entityData.position.y[entityIdx] = gridY + props.dstTileH - colOffY - colH;
        entityData.position.initialW[entityIdx] = w;
        entityData.position.initialH[entityIdx] = h;
        entityData.position.w[entityIdx] = entityData.position.initialW[entityIdx];
        entityData.position.h[entityIdx] = entityData.position.initialH[entityIdx];
        entityData.animation.frame.collision.initialOffX[entityIdx][0] = colOffX;
        entityData.animation.frame.collision.initialOffY[entityIdx][0] = colOffY;
        entityData.animation.frame.collision.initialW[entityIdx][0] = colW;
        entityData.animation.frame.collision.initialH[entityIdx][0] = colH;
        entityData.animation.frame.collision.offX[entityIdx][0] = colOffX;
        entityData.animation.frame.collision.offY[entityIdx][0] = colOffY;
        entityData.animation.frame.collision.w[entityIdx][0] = colW * entityData.scale.value[entityIdx];
        entityData.animation.frame.collision.h[entityIdx][0] = colH * entityData.scale.value[entityIdx];
        entityData.animation.animationType[entityIdx] = AnimationType::None;
        entityData.animation.frameCount[entityIdx] = 1;
        entityData.animation.frame.frameDuration[entityIdx][0] = 0;
        entityData.animation.frameIndex[entityIdx] = 0;
        entityData.animation.cycleDuration[entityIdx] = 0;
        entityData.animation.animationStartTime[entityIdx] = 0;
    }
    else
    {
        loadTileAnimation(
            entityData.animation,
            entityIdx,
            tileset,
            entityTileIdx,
            props,
            entityData.scale.value[entityIdx]);
        if (tileArrayIdx != UINT32_MAX)
        {
            SDL_Point grid = decodeGridIndex((int)tileArrayIdx, props.mapW);
            entityData.position.x[entityIdx] = grid.x * props.dstTileW;
            entityData.position.y[entityIdx] = grid.y * props.dstTileH;
        }
        entityData.position.initialW[entityIdx] = props.srcTileW;
        entityData.position.initialH[entityIdx] = props.srcTileH;
        entityData.position.w[entityIdx] = entityData.position.initialW[entityIdx];
        entityData.position.h[entityIdx] = entityData.position.initialH[entityIdx];
    }

    entityData.position.w[entityIdx] = entityData.position.initialW[entityIdx] * entityData.scale.value[entityIdx];
    entityData.position.h[entityIdx] = entityData.position.initialH[entityIdx] * entityData.scale.value[entityIdx];
    entityData.position.dirty[entityIdx] = true;

    entityData.rotation.initialAngle[entityIdx] = getTileFloatProp(tileset, entityTileIdx, "angle", 0.0f);
    entityData.rotation.initialRotate[entityIdx] = getTileFloatProp(tileset, entityTileIdx, "rotate", 0.0f);
    entityData.rotation.rotate[entityIdx] = entityData.rotation.initialRotate[entityIdx];

    FacingDirection entityFacing = getTileStringProp(tileset, entityTileIdx, "facing") == "left" ? FacingDirection::Left : FacingDirection::Right;
    entityData.facing.facing[entityIdx] = entityFacing;
    entityData.facing.initialFacing[entityIdx] = entityFacing;
    entityData.facing.dirty[entityIdx] = true;

    entityData.tint.r[entityIdx] = CLEAR_TINT_R;
    entityData.tint.g[entityIdx] = CLEAR_TINT_G;
    entityData.tint.b[entityIdx] = CLEAR_TINT_B;
    entityData.tint.a[entityIdx] = CLEAR_TINT_A;
    entityData.tint.damageTimer[entityIdx] = 0.0f;
    entityData.tint.isPoisoned[entityIdx] = false;
    entityData.tint.isSlowed[entityIdx] = false;
}
