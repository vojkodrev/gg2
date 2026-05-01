#pragma once
#include <cstdint>

const int SCREEN_W = 1280;
const int SCREEN_H = 720;

const int MAX_TILES = 1000;
const int MAX_NPCS = 100;
const int MAX_OBJECTS = 100;
const int MAX_RENDER_BUFFER = 100;
const int MAX_COLLISION_PAIRS = 2048;
const int MAX_PATROL_POINTS = 16;
const int MAX_ASTARS = 20;

const int ASTAR_SEARCH_PAD = 200;
const int ASTAR_HEAP_SIZE = 65536;
const int ASTAR_HASH_SIZE = 65536;  // power of 2, keep load < 50%
const int ASTAR_MAX_PATH  = 1024;

const uint16_t COLLISION_ENTITY_PLAYER = 0;

const float PLAYER_SPEED      = 100.0f;

const float NPC_MONSTER_SPEED     = 100.0f;
const int   NPC_MONSTER_PATH_STEP    = 8;
const float NPC_DETECT_RADIUS  = 200.0f;
const float NPC_ATTACK_REACH   = 10.0f;
const float NPC_LEASH_RADIUS   = 400.0f;
