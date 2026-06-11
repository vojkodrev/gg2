#include "LoadPlayer.h"
#include "FindLayer.h"
#include "LoadEntityBase.h"
#include "LoadEquipment.h"
#include "../../utils/groups/AllocGroup.h"
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
        loadEquipment(ctx.data.player.equipment, 0, tileset, idx, props);
        ctx.data.player.groupId = allocGroup(ctx.data.groups);
        break;
    }
}
