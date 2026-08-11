#include "LoadNPCs.h"
#include "FindLayer.h"
#include "properties/GetTileIntProp.h"
#include "properties/GetTileStringProp.h"
#include "LoadEntityBase.h"
#include "LoadEquipment.h"
#include "LoadRangedCollision.h"
#include "LoadHealthbar.h"
#include "LoadManabar.h"
#include "../gameplay/statistics/SetHp.h"
#include "../gameplay/ai/ResetNpcCombatState.h"
#include "../../structs/core/constants/NpcConstants.h"
#include "../../structs/core/constants/NpcMonsterConstants.h"
#include "../../structs/core/constants/NpcPetConstants.h"
#include "../../structs/core/constants/IndexConstants.h"
#include "../../structs/equipment/WeaponType.h"
#include "../../utils/groups/GroupAlloc.h"
#include "../../utils/timers/RandomTimer.h"
#include <tmxlite/TileLayer.hpp>
#include <cstdio>

void loadNPCs(Context &ctx, const tmx::Map &map, const tmx::Tileset &tileset)
{
    auto &props = ctx.data.tileMapProps;
    auto &npc = ctx.data.npc;
    auto &player = ctx.data.player;
    auto &npcTiles = findLayer(map, "NPC")->getLayerAs<tmx::TileLayer>().getTiles();
    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        npc.active[i] = false;
        npc.initialized[i] = false;
        for (int f = 0; f < MAX_ANIMATION_FRAMES; f++)
            npc.rangedCollision.anchor.exists[i][f] = false;
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

        if (npc.group.id[n] == INVALID_ID)
            npc.group.id[n] = groupAlloc(ctx.data.groups);

        if (npc.group.id[n] == INVALID_ID)
            break;

        uint32_t idx = npcTiles[i].ID - props.firstGid;
        loadEntityBase(npc.base, n, tileset, idx, props, i);
        setHp(npc.statistics, n, NPC_HP);
        npc.statistics.health.maxHp[n] = NPC_HP;
        resetNpcCombatState(ctx, n);
        npc.ai.spawn.x[n] = npc.base.position.x[n];
        npc.ai.spawn.y[n] = npc.base.position.y[n];
        npc.ai.patrol.index[n] = 0;
        npc.ai.state[n] = NPCAiState::Idle;
        npc.ai.attackedTimer[n] = 0.0f;
        npc.ai.idleTimer[n] = randomTimer(NPC_IDLE_TIME_MIN, NPC_IDLE_TIME_MAX);
        npc.ai.repathTimer[n] = 0.0f;
        npc.ai.pathTargetCheckTimer[n] = 0.0f;
        npc.ai.pursueTargetRangeCheckTimer[n] = 0.0f;
        npc.ai.rangedAttackTargetTooCloseCheckTimer[n] = 0.0f;
        npc.ai.rangedAttackStaggerTimer[n] = 0.0f;
        npc.ai.targetTooClose[n] = false;
        npc.ai.flipTimer[n] = 0.0f;
        npc.ai.targetVisibleTimer[n] = 0.0f;
        npc.ai.targetVisible[n] = false;

        loadEquipment(npc.equipment, n, tileset, idx, props);
        if (npc.equipment.weapon.type[n] == WeaponType::Ranged)
            loadRangedCollision(
                npc.rangedCollision,
                npc.base,
                n,
                npc.equipment.weapon.base.animation.frameCount[n]);
        loadHealthbar(npc.healthbar, n, tileset, idx, props);
        loadManabar(npc.manabar, n, tileset, idx, props);

        const std::string aiType = getTileStringProp(tileset, idx, "AI");
        npc.ai.type[n] = NPCAiType::None;
        if (aiType == "monsterMelee")
            npc.ai.type[n] = NPCAiType::MonsterMelee;
        else if (aiType == "monsterRanged")
            npc.ai.type[n] = NPCAiType::MonsterRanged;
        else if (aiType == "pet")
            npc.ai.type[n] = NPCAiType::Pet;
        else if (aiType == "friendly")
            npc.ai.type[n] = NPCAiType::Friendly;

        if (npc.ai.type[n] == NPCAiType::MonsterRanged)
        {
            npc.statistics.mana.mana[n] = NPC_MANA;
            npc.statistics.mana.maxMana[n] = NPC_MANA;
            npc.statistics.mana.dirty[n] = true;
        }
        else if (npc.ai.type[n] == NPCAiType::Pet)
        {
            player.petId = (int)n;
            npc.statistics.mana.mana[n] = NPC_PET_MANA;
            npc.statistics.mana.maxMana[n] = NPC_PET_MANA;
            npc.statistics.mana.dirty[n] = true;
        }
        npc.concussiveShotCooldownTimer[n] = 0.0f;

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
