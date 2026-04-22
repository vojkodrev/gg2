#pragma once
#include <cstdint>

const int MAX_TILES = 1000;
const int MAX_NPCS = 100;
const int MAX_OBJECTS = 100;
const int MAX_RENDER_BUFFER = 100;
const int MAX_COLLISION_PAIRS = 2048;
const int MAX_PATROL_POINTS = 16;

const uint16_t COLLISION_ENTITY_PLAYER = 0;

const float NPC_MONSTER_SPEED  = 100.0f;
const float NPC_DETECT_RADIUS  = 200.0f;
const float NPC_ATTACK_REACH   = 40.0f;
const float NPC_LEASH_RADIUS   = 400.0f;
