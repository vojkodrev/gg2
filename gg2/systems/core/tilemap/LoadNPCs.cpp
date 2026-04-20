#include "LoadNPCs.h"
#include "FindLayer.h"
#include "GetCollision.h"
#include <tmxlite/TileLayer.hpp>

void LoadNPCs(Context &ctx, const tmx::Map &map, const tmx::Tileset &tileset)
{
    auto &props = ctx.data.tileMapProps;
    auto &npc = ctx.data.npc;
    auto &npcTiles = FindLayer(map, "NPC")->getLayerAs<tmx::TileLayer>().getTiles();
    npc.npcCount = 0;
    for (uint32_t i = 0; i < npcTiles.size(); i++)
    {
        if (npcTiles[i].ID == 0)
            continue;
        uint32_t n = npc.npcCount++;
        uint32_t idx = npcTiles[i].ID - props.firstGid;
        npc.src.x[n] = idx % props.columns * props.srcTileW;
        npc.src.y[n] = idx / props.columns * props.srcTileH;
        npc.src.w[n] = props.srcTileW;
        npc.src.h[n] = props.srcTileH;
        npc.position.x[n] = i % props.mapW * props.dstTileW;
        npc.position.y[n] = i / props.mapW * props.dstTileH;
        npc.position.w[n] = props.dstTileW;
        npc.position.h[n] = props.dstTileH;
        GetCollision(tileset, idx, npc.collision.offX[n], npc.collision.offY[n], npc.collision.w[n], npc.collision.h[n]);
    }
}
