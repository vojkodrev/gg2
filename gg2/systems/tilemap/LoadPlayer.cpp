#include "LoadPlayer.h"
#include "FindLayer.h"
#include "GetTileIndex.h"
#include "LoadEntityBase.h"
#include "LoadEquipment.h"
#include "LoadProgressBar.h"
#include "../gameplay/statistics/SetHp.h"
#include "../../structs/core/constants/IndexConstants.h"
#include "../../structs/core/constants/ZIndexConstants.h"
#include "../../structs/core/constants/PlayerConstants.h"
#include "../../utils/groups/GroupAlloc.h"
#include <tmxlite/TileLayer.hpp>

void loadPlayer(Context &ctx, const tmx::Map &map, const tmx::Tileset &tileset)
{
    auto &props = ctx.data.tileMapProps;
    auto &playerTiles = findLayer(map, "Player")->getLayerAs<tmx::TileLayer>().getTiles();

    for (int i = 0; i < (int)playerTiles.size(); i++)
    {
        if (playerTiles[i].ID == 0)
            continue;
        uint32_t idx = getTileIndex(playerTiles[i].ID, props);
        loadEntityBase(ctx.data.player.base, 0, tileset, idx, props, (uint32_t)i);
        setHp(ctx.data.player.statistics, 0, PLAYER_HP);
        ctx.data.player.statistics.health.maxHp[0] = PLAYER_HP;
        ctx.data.player.statistics.mana.mana[0] = PLAYER_MANA;
        ctx.data.player.statistics.mana.maxMana[0] = PLAYER_MANA;
        ctx.data.player.statistics.mana.dirty[0] = true;
        ctx.data.player.petId = INVALID_ID;
        ctx.data.player.selectedNpc = INVALID_ID;
        ctx.data.player.previousSelectedNpc = INVALID_ID;
        ctx.data.player.selectedEffectId = INVALID_ID;
        ctx.data.player.targetVisibleTimer = 0.0f;
        ctx.data.player.targetVisible = false;
        loadEquipment(ctx.data.player.equipment, 0, tileset, idx, props);
        loadProgressBar(
            ctx.data.player.healthbar,
            0,
            tileset,
            idx,
            props,
            "healthbar");
        loadProgressBar(
            ctx.data.player.manabar,
            0,
            tileset,
            idx,
            props,
            "manabar");
        ctx.data.player.group.id[0] = groupAlloc(ctx.data.groups);
        ctx.data.player.zIndex[0] = PARENT_Z_INDEX;
        break;
    }
}
