#include "LoadTileMap.h"
#include "LoadGround.h"
#include "LoadPlayer.h"
#include "LoadNPCs.h"
#include "LoadObjects.h"

void LoadTileMap(Context &ctx, const tmx::Map &map)
{
    auto &tileset = map.getTilesets()[0];
    LoadGround(ctx, map, tileset);
    LoadPlayer(ctx, map, tileset);
    LoadNPCs(ctx, map, tileset);
    LoadObjects(ctx, map, tileset);
}
