#pragma once
#include "../ui/actionbar/ActionBar.h"
#include "TileMapProperties.h"
#include "TileMap.h"
#include "Player.h"
#include "Camera.h"
#include "NPC.h"
#include "Object.h"
#include "Effect.h"
#include "EffectTemplate.h"
#include "Groups.h"
#include "constants/GroupConstants.h"
#include "../input/ActionState.h"
#include "../debug/DebugFps.h"
#include "../debug/DebugState.h"

struct Data
{
    ActionBar actionBar;
    TileMapProperties tileMapProps;
    TileMap tileMap;
    Player player;
    Camera camera;
    NPC npc;
    Object object;
    Groups<MAX_GROUPS> groups;
    Effect effect;
    EffectTemplate effectTemplate;
    ActionState action;
    DebugFps fps;
    DebugState debug;
};
