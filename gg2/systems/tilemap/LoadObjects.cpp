#include "LoadObjects.h"
#include "FindLayer.h"
#include "IsMarker.h"
#include "properties/GetTileFloatProp.h"
#include "properties/GetTilePropInt.h"
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
        if (isMarker(tileset, idx))
        {
            object.animation.frame.src.x[n][0] = getTileProp(tileset, idx, "x");
            object.animation.frame.src.y[n][0] = getTileProp(tileset, idx, "y");
            object.animation.frame.src.w[n][0] = getTileProp(tileset, idx, "w");
            object.animation.frame.src.h[n][0] = getTileProp(tileset, idx, "h");
            float scale = getTileFloatProp(tileset, idx, "scale", 1.0f);
            float colOffX = (float)getTileProp(tileset, idx, "colOffX") * scale;
            float colOffY = (float)getTileProp(tileset, idx, "colOffY") * scale;
            float colW = (float)getTileProp(tileset, idx, "colW") * scale;
            float colH = (float)getTileProp(tileset, idx, "colH") * scale;
            float w = (float)getTileProp(tileset, idx, "w") * scale;
            float h = (float)getTileProp(tileset, idx, "h") * scale;
            SDL_Point grid = decodeGridIndex(i, props.mapW);
            float gridX = (float)(grid.x * props.dstTileW);
            float gridY = (float)(grid.y * props.dstTileH);

            object.position.x[n] = gridX + (props.dstTileW - colW) / 2.0f - colOffX;
            object.position.y[n] = gridY + props.dstTileH - colOffY - colH;
            object.position.w[n] = w;
            object.position.h[n] = h;
            object.animation.frame.collision.offX[n][0] = colOffX;
            object.animation.frame.collision.offY[n][0] = colOffY;
            object.animation.frame.collision.w[n][0] = colW;
            object.animation.frame.collision.h[n][0] = colH;
            object.animation.frameCount[n] = 1;
            object.animation.frame.frameDuration[n][0] = 0;
            object.animation.frameIndex[n] = 0;
            object.animation.animationStartTime[n] = 0;
        }
        else
        {
            loadTileAnimation(object.animation, n, tileset, idx, props);

            SDL_Point grid = decodeGridIndex(i, props.mapW);
            object.position.x[n] = grid.x * props.dstTileW;
            object.position.y[n] = grid.y * props.dstTileH;
            object.position.w[n] = props.dstTileW;
            object.position.h[n] = props.dstTileH;
        }
    }
}
