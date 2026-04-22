#include "LoadNPCs.h"
#include "FindLayer.h"
#include "GetCollision.h"
#include "GetTileProp.h"
#include "RandomIdleTimer.h"
#include <tmxlite/TileLayer.hpp>
#include <cstdio>

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
        npc.ai.spawn.x[n] = npc.position.x[n];
        npc.ai.spawn.y[n] = npc.position.y[n];
        npc.ai.patrolIndex[n] = 0;
        npc.ai.state[n] = NPCAiState::Idle;
        npc.ai.idleTimer[n] = RandomIdleTimer();

        npc.ai.type[n] = (NPCAiType)(int)GetTileProp(tileset, idx, "AI");

        npc.ai.patrolCount[n] = (uint32_t)GetTileProp(tileset, idx, "patrolCount");
        for (uint32_t p = 0; p < npc.ai.patrolCount[n] && p < MAX_PATROL_POINTS; p++)
        {
            char key[16];
            snprintf(key, sizeof(key), "patrol%02u", p + 1);
            std::string val = GetTileStringProp(tileset, idx, key);
            sscanf(val.c_str(), "%f,%f", &npc.ai.patrol.x[n][p], &npc.ai.patrol.y[n][p]);
        }
    }
}
