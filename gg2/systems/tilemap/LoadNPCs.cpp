#include "LoadNPCs.h"
#include "FindLayer.h"
#include "properties/GetTileFloatProp.h"
#include "properties/GetTileIntProp.h"
#include "properties/GetTileStringProp.h"
#include "LoadTileAnimation.h"
#include "LoadWeapon.h"
#include "DecodeGridIndex.h"
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
        loadTileAnimation(npc.animation, n, tileset, idx, props);
        SDL_Point grid = decodeGridIndex(i, props.mapW);
        npc.position.x[n] = grid.x * props.dstTileW;
        npc.position.y[n] = grid.y * props.dstTileH;
        npc.position.initialW[n] = props.dstTileW;
        npc.position.initialH[n] = props.dstTileH;
        npc.position.w[n] = npc.position.initialW[n];
        npc.position.h[n] = npc.position.initialH[n];
        npc.scale[n] = getTileFloatProp(tileset, idx, "scale", 1.0f);
        npc.ai.spawn.x[n] = npc.position.x[n];
        npc.ai.spawn.y[n] = npc.position.y[n];
        npc.ai.patrol.index[n] = 0;
        npc.ai.state[n] = NPCAiState::Idle;
        npc.ai.idleTimer[n] = randomTimer(NPC_IDLE_TIME_MIN, NPC_IDLE_TIME_MAX);
        npc.ai.repathTimer[n] = 0.0f;

        FacingDirection f = getTileStringProp(tileset, idx, "facing") == "right" ? FacingDirection::Right : FacingDirection::Left;
        npc.facing.facing[n] = f;
        npc.facing.initialFacing[n] = f;

        loadWeapon(npc.equipment.weapon, n, tileset, idx, props);

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
