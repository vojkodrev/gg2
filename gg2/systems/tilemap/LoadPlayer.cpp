#include "LoadPlayer.h"
#include "FindLayer.h"
#include "LoadEntityBase.h"
#include "LoadEquipment.h"
#include "LoadHealthbar.h"
#include "../gameplay/statistics/SetHp.h"
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
        uint32_t idx = playerTiles[i].ID - props.firstGid;
        loadEntityBase(ctx.data.player.base, 0, tileset, idx, props, (uint32_t)i);
        setHp(ctx.data.player.statistics, 0, PLAYER_HP);
        ctx.data.player.statistics.maxHp[0] = PLAYER_HP;
        ctx.data.player.selectedNpc = -1;
        ctx.data.player.previousSelectedNpc = -1;
        ctx.data.player.selectedEffectId = -1;
        loadEquipment(ctx.data.player.equipment, 0, tileset, idx, props);
        loadHealthbar(ctx.data.player.healthbar, 0, tileset, idx, props);
        ctx.data.player.groupId = groupAlloc(ctx.data.groups);
        break;
    }
}
