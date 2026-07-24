#pragma once

const int   NPC_HP               = 1000;
const float NPC_MONSTER_SPEED    = 100.0f;
const int   NPC_MONSTER_PATH_STEP = 8;
const float NPC_DETECT_RADIUS    = 300.0f;
const float NPC_MELEE_ATTACK_REACH = 10.0f;
const float NPC_MELEE_AUTO_ATTACK_DELAY = 1.5f;
const int   NPC_MELEE_AUTO_ATTACK_DAMAGE = 200;
const int   NPC_MELEE_AUTO_ATTACK_DAMAGE_RANDOM_RANGE = 50;
const float NPC_RANGED_AUTO_ATTACK_DELAY = 1.5f;
const int   NPC_PROJECTILE_DAMAGE = 100;
const int   NPC_PROJECTILE_DAMAGE_RANDOM_RANGE = 50;
const float PET_MELEE_AUTO_ATTACK_DELAY = 1.5f;
const int   PET_DAMAGE = 100;
const int   PET_DAMAGE_RANDOM_RANGE = 50;
const float NPC_ATTACKED_TIME    = 5.0f;
const float NPC_IDLE_TIME_MIN    = 1.0f;
const float NPC_IDLE_TIME_MAX    = 3.0f;
const float NPC_REPATH_TIME      = 2.0f;
const float NPC_PURSUE_TARGET_RANGE_CHECK_TIME = 0.25f;
const float NPC_RANGED_ATTACK_TARGET_TOO_CLOSE_CHECK_TIME = 0.25f;
const float NPC_TARGET_VISIBLE_CHECK_TIME = 0.25f;
const float NPC_TARGET_VISIBLE_AMMO_BUFFER = 2.0f;
const float NPC_PATH_TARGET_CHECK_TIME = 0.25f;
const float NPC_PATH_TARGET_MOVE_THRESHOLD = 64.0f;
