#include "LoadNPCs.h"
#include "FindLayer.h"
#include "properties/GetTileIntProp.h"
#include "properties/GetTileStringProp.h"
#include "LoadEntityBase.h"
#include "LoadEquipment.h"
#include "../../structs/core/constants/NpcMonsterConstants.h"
#include "../../utils/npc/RandomTimer.h"
#include <tmxlite/TileLayer.hpp>
#include <cstdio>

void loadNPCs(Context &ctx, const tmx::Map &map, const tmx::Tileset &tileset)
{
    auto &props = ctx.data.tileMapProps;
    auto &npc = ctx.data.npc;
    auto &npcTiles = findLayer(map, "NPC")->getLayerAs<tmx::TileLayer>().getTiles();
    npc.npcCount = 0;
    for (uint32_t i = 0; i < npcTiles.size(); i++)
    {
        if (npcTiles[i].ID == 0)
            continue;
        uint32_t n = npc.npcCount++;
        uint32_t idx = npcTiles[i].ID - props.firstGid;
        loadEntityBase(npc.base, n, tileset, idx, props, i);
        npc.ai.spawn.x[n] = npc.base.position.x[n];
        npc.ai.spawn.y[n] = npc.base.position.y[n];
        npc.ai.patrol.index[n] = 0;
        npc.ai.state[n] = NPCAiState::Idle;
        npc.ai.idleTimer[n] = randomTimer(NPC_IDLE_TIME_MIN, NPC_IDLE_TIME_MAX);
        npc.ai.repathTimer[n] = 0.0f;

        loadEquipment(npc.equipment, n, tileset, idx, props);

        npc.ai.type[n] = (NPCAiType)(int)getTileIntProp(tileset, idx, "AI");

        npc.ai.patrol.count[n] = (uint32_t)getTileIntProp(tileset, idx, "patrolCount");
        for (uint32_t p = 0; p < npc.ai.patrol.count[n] && p < MAX_PATROL_POINTS; p++)
        {
            char key[16];
            snprintf(key, sizeof(key), "patrol%02u", p + 1);
            std::string val = getTileStringProp(tileset, idx, key);
            sscanf(val.c_str(), "%f,%f", &npc.ai.patrol.point.x[n][p], &npc.ai.patrol.point.y[n][p]);
        }
    }
}
