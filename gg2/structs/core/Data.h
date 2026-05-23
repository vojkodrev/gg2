#pragma once
#include "TileMapProperties.h"
#include "TileMap.h"
#include "Player.h"
#include "Camera.h"
#include "NPC.h"
#include "Object.h"
#include "DebugState.h"

struct Data
{
    TileMapProperties tileMapProps;
    TileMap tileMap;
    Player player;
    Camera camera;
    NPC npc;
    Object object;
    DebugState debug;
};
