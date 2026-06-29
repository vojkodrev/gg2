#include "LoadTileMap.h"
#include "LoadGround.h"
#include "LoadEffects.h"
#include "LoadPlayer.h"
#include "LoadNPCs.h"
#include "LoadObjects.h"
#include "LoadActionBar.h"

void loadTileMap(Context &ctx, const tmx::Map &map)
{
    auto &tileset = map.getTilesets()[0];
    loadGround(ctx, map, tileset);
    loadEffects(ctx, tileset);
    loadPlayer(ctx, map, tileset);
    loadNPCs(ctx, map, tileset);
    loadObjects(ctx, map, tileset);
    loadActionBar(ctx, tileset);
}
