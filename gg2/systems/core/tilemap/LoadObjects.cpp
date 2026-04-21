#include "LoadObjects.h"
#include "FindLayer.h"
#include "GetCollision.h"
#include "IsMarker.h"
#include "GetTileProp.h"
#include <tmxlite/TileLayer.hpp>

void LoadObjects(Context &ctx, const tmx::Map &map, const tmx::Tileset &tileset)
{
    auto &props = ctx.data.tileMapProps;
    auto &object = ctx.data.object;
    auto &objectTiles = FindLayer(map, "Object")->getLayerAs<tmx::TileLayer>().getTiles();
    object.objectCount = 0;
    for (uint32_t i = 0; i < objectTiles.size(); i++)
    {
        if (objectTiles[i].ID == 0)
            continue;
        uint32_t n = object.objectCount++;
        uint32_t idx = objectTiles[i].ID - props.firstGid;
        if (IsMarker(tileset, idx))
        {
            object.src.x[n] = GetTileProp(tileset, idx, "x");
            object.src.y[n] = GetTileProp(tileset, idx, "y");
            object.src.w[n] = GetTileProp(tileset, idx, "w");
            object.src.h[n] = GetTileProp(tileset, idx, "h");
            float colOffX = (float)GetTileProp(tileset, idx, "colOffX");
            float colOffY = (float)GetTileProp(tileset, idx, "colOffY");
            float colW = (float)GetTileProp(tileset, idx, "colW");
            float colH = (float)GetTileProp(tileset, idx, "colH");
            float w = (float)GetTileProp(tileset, idx, "w");
            float h = (float)GetTileProp(tileset, idx, "h");
            float gridX = (float)(i % props.mapW * props.dstTileW);
            float gridY = (float)(i / props.mapW * props.dstTileH);

            // center collision box horizontally in tile, then shift by colOffX
            // align collision box to tile bottom, then shift up by colOffY and colH
            object.position.x[n] = gridX + (props.dstTileW - colW) / 2.0f - colOffX;
            object.position.y[n] = gridY + props.dstTileH - colOffY - colH;

            object.position.w[n] = w;
            object.position.h[n] = h;
            object.collision.offX[n] = colOffX;
            object.collision.offY[n] = colOffY;
            object.collision.w[n] = colW;
            object.collision.h[n] = colH;
        }
        else
        {
            object.src.x[n] = idx % props.columns * props.srcTileW;
            object.src.y[n] = idx / props.columns * props.srcTileH;
            object.src.w[n] = props.srcTileW;
            object.src.h[n] = props.srcTileH;
            object.position.x[n] = i % props.mapW * props.dstTileW;
            object.position.y[n] = i / props.mapW * props.dstTileH;
            object.position.w[n] = props.dstTileW;
            object.position.h[n] = props.dstTileH;
            GetCollision(tileset, idx, object.collision.offX[n], object.collision.offY[n], object.collision.w[n], object.collision.h[n]);
        }
    }
}
