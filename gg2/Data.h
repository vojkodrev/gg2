#pragma once
#include "TileMapProperties.h"
#include "TileMap.h"
#include "Player.h"
#include "NPC.h"

struct Data
{
    TileMapProperties tileMapProps;
    TileMap tileMap;
    Player player;
    NPC npc;
};
