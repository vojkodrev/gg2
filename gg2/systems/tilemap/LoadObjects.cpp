#include "LoadObjects.h"
#include "FindLayer.h"
#include "IsMarker.h"
#include "properties/GetTileFloatProp.h"
#include "properties/GetTileIntProp.h"
#include "LoadTileAnimation.h"
#include "DecodeGridIndex.h"
#include <tmxlite/TileLayer.hpp>

void loadObjects(Context &ctx, const tmx::Map &map, const tmx::Tileset &tileset)
{
    auto &props = ctx.data.tileMapProps;
    auto &object = ctx.data.object;
    auto &objectTiles = findLayer(map, "Object")->getLayerAs<tmx::TileLayer>().getTiles();
    object.objectCount = 0;
    for (uint32_t i = 0; i < objectTiles.size(); i++)
    {
        if (objectTiles[i].ID == 0)
            continue;
        uint32_t n = object.objectCount++;
        uint32_t idx = objectTiles[i].ID - props.firstGid;
        float scale = getTileFloatProp(tileset, idx, "scale", 1.0f);
        object.scale[n] = scale;
        if (isMarker(tileset, idx))
        {
            object.animation.frame.src.x[n][0] = getTileIntProp(tileset, idx, "x");
            object.animation.frame.src.y[n][0] = getTileIntProp(tileset, idx, "y");
            object.animation.frame.src.w[n][0] = getTileIntProp(tileset, idx, "w");
            object.animation.frame.src.h[n][0] = getTileIntProp(tileset, idx, "h");
            object.animation.frame.src.rotate[n][0] = 0;
            float colOffX = (float)getTileIntProp(tileset, idx, "colOffX");
            float colOffY = (float)getTileIntProp(tileset, idx, "colOffY");
            float colW = (float)getTileIntProp(tileset, idx, "colW");
            float colH = (float)getTileIntProp(tileset, idx, "colH");
            float w = (float)getTileIntProp(tileset, idx, "w");
            float h = (float)getTileIntProp(tileset, idx, "h");
            SDL_Point grid = decodeGridIndex(i, props.mapW);
            float gridX = (float)(grid.x * props.dstTileW);
            float gridY = (float)(grid.y * props.dstTileH);

            object.position.x[n] = gridX + (props.dstTileW - colW) / 2.0f - colOffX;
            object.position.y[n] = gridY + props.dstTileH - colOffY - colH;
            object.position.initialW[n] = w;
            object.position.initialH[n] = h;
            object.position.w[n] = object.position.initialW[n];
            object.position.h[n] = object.position.initialH[n];
            object.animation.frame.collision.offX[n][0] = colOffX;
            object.animation.frame.collision.offY[n][0] = colOffY;
            object.animation.frame.collision.w[n][0] = colW;
            object.animation.frame.collision.h[n][0] = colH;
            object.animation.animationType[n] = AnimationType::None;
            object.animation.frameCount[n] = 1;
            object.animation.frame.frameDuration[n][0] = 0;
            object.animation.frameIndex[n] = 0;
            object.animation.animationStartTime[n] = 0;
            object.animation.animationStopTime[n] = 0;
        }
        else
        {
            loadTileAnimation(object.animation, n, tileset, idx, props);

            SDL_Point grid = decodeGridIndex(i, props.mapW);
            object.position.x[n] = grid.x * props.dstTileW;
            object.position.y[n] = grid.y * props.dstTileH;
            object.position.initialW[n] = props.dstTileW;
            object.position.initialH[n] = props.dstTileH;
            object.position.w[n] = object.position.initialW[n];
            object.position.h[n] = object.position.initialH[n];
        }
    }
}
