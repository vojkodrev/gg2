#include "LoadObjects.h"
#include "FindLayer.h"
#include "GetCollision.h"
#include "IsMarker.h"
#include "GetTileProp.h"
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
            float gridX = (float)(i % props.mapW * props.dstTileW);
            float gridY = (float)(i / props.mapW * props.dstTileH);

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
        }
        else
        {
            // find animation frames for this tile
            const tmx::Tileset::Tile *tileData = nullptr;
            for (auto &t : tileset.getTiles())
                if (t.ID == idx) { tileData = &t; break; }

            SDL_FRect col = getCollision(tileset, idx);

            if (tileData && !tileData->animation.frames.empty())
            {
                int frameCount = (int)tileData->animation.frames.size();
                if (frameCount > MAX_ANIMATION_FRAMES) frameCount = MAX_ANIMATION_FRAMES;
                object.animation.frameCount[n] = frameCount;
                for (int f = 0; f < frameCount; f++)
                {
                    uint32_t fid = tileData->animation.frames[f].tileID;
                    object.animation.frame.src.x[n][f] = fid % props.columns * props.srcTileW;
                    object.animation.frame.src.y[n][f] = fid / props.columns * props.srcTileH;
                    object.animation.frame.src.w[n][f] = props.srcTileW;
                    object.animation.frame.src.h[n][f] = props.srcTileH;
                    object.animation.frame.collision.offX[n][f] = col.x;
                    object.animation.frame.collision.offY[n][f] = col.y;
                    object.animation.frame.collision.w[n][f] = col.w;
                    object.animation.frame.collision.h[n][f] = col.h;
                    object.animation.frame.frameDuration[n][f] = tileData->animation.frames[f].duration;
                }
            }
            else
            {
                object.animation.frameCount[n] = 1;
                object.animation.frame.src.x[n][0] = idx % props.columns * props.srcTileW;
                object.animation.frame.src.y[n][0] = idx / props.columns * props.srcTileH;
                object.animation.frame.src.w[n][0] = props.srcTileW;
                object.animation.frame.src.h[n][0] = props.srcTileH;
                object.animation.frame.collision.offX[n][0] = col.x;
                object.animation.frame.collision.offY[n][0] = col.y;
                object.animation.frame.collision.w[n][0] = col.w;
                object.animation.frame.collision.h[n][0] = col.h;
                object.animation.frame.frameDuration[n][0] = 0;
            }

            object.position.x[n] = i % props.mapW * props.dstTileW;
            object.position.y[n] = i / props.mapW * props.dstTileH;
            object.position.w[n] = props.dstTileW;
            object.position.h[n] = props.dstTileH;
        }
        object.animation.frameIndex[n] = 0;
        object.animation.animationStartTime[n] = 0;
    }
}
