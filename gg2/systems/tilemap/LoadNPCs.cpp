#include "LoadNPCs.h"
#include "FindLayer.h"
#include "properties/GetTileIntProp.h"
#include "properties/GetTileStringProp.h"
#include "LoadEntityBase.h"
#include "LoadEquipment.h"
#include "LoadHealthbar.h"
#include "../gameplay/statistics/SetHp.h"
#include "../gameplay/ai/ClearNpcAiTarget.h"
#include "../../structs/core/constants/NpcConstants.h"
#include "../../structs/core/constants/NpcMonsterConstants.h"
#include "../../utils/groups/GroupAlloc.h"
#include "../../utils/timers/RandomTimer.h"
#include <tmxlite/TileLayer.hpp>
#include <cstdio>

void loadNPCs(Context &ctx, const tmx::Map &map, const tmx::Tileset &tileset)
{
    auto &props = ctx.data.tileMapProps;
    auto &npc = ctx.data.npc;
    auto &npcTiles = findLayer(map, "NPC")->getLayerAs<tmx::TileLayer>().getTiles();
    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        npc.active[i] = false;
        npc.initialized[i] = false;
    }

    uint32_t npcCount = 0;
    for (uint32_t i = 0; i < npcTiles.size(); i++)
    {
        if (npcTiles[i].ID == 0)
            continue;

        if (npcCount >= MAX_NPCS)
            break;

        uint32_t n = npcCount++;
        npc.active[n] = true;
        npc.initialized[n] = true;

        if (npc.groupId[n] == -1)
            npc.groupId[n] = groupAlloc(ctx.data.groups);

        if (npc.groupId[n] == -1)
            break;

        uint32_t idx = npcTiles[i].ID - props.firstGid;
        loadEntityBase(npc.base, n, tileset, idx, props, i);
        setHp(npc.statistics, n, NPC_HP);
        npc.statistics.health.maxHp[n] = NPC_HP;
        npc.concussiveShotDebuffTimer[n] = 0.0f;
        npc.serpentStingDebuffTimer[n] = 0.0f;
        npc.ai.spawn.x[n] = npc.base.position.x[n];
        npc.ai.spawn.y[n] = npc.base.position.y[n];
        npc.ai.patrol.index[n] = 0;
        npc.ai.state[n] = NPCAiState::Idle;
        clearNpcAiTarget(n, ctx);
        npc.ai.idleTimer[n] = randomTimer(NPC_IDLE_TIME_MIN, NPC_IDLE_TIME_MAX);
        npc.ai.repathTimer[n] = 0.0f;

        loadEquipment(npc.equipment, n, tileset, idx, props);
        loadHealthbar(npc.healthbar, n, tileset, idx, props);

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
