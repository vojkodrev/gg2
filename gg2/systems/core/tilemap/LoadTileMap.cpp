#include "LoadTileMap.h"
#include "LoadGround.h"
#include "LoadPlayer.h"
#include "LoadNPCs.h"

void LoadTileMap(Context &ctx, const tmx::Map &map)
{
    auto &tileset = map.getTilesets()[0];
    LoadGround(ctx, map, tileset);
    LoadPlayer(ctx, map, tileset);
    LoadNPCs(ctx, map, tileset);
}
