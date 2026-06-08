#pragma once
#include "CollisionConstants.h"
#include "NpcConstants.h"
#include <cstdint>

inline uint16_t colIdNpc(uint32_t i)    { return (uint16_t)(1 + i); }
inline uint16_t colIdObject(uint32_t i) { return (uint16_t)(1 + MAX_NPCS + i); }

inline bool colIdIsPlayer(uint16_t id) { return id == COLLISION_ENTITY_PLAYER; }
inline bool colIdIsNpc(uint16_t id)    { return id >= 1 && id <= (uint16_t)MAX_NPCS; }
inline bool colIdIsObject(uint16_t id) { return id > (uint16_t)MAX_NPCS; }

inline uint32_t colIdNpcIndex(uint16_t id)    { return id - 1; }
inline uint32_t colIdObjectIndex(uint16_t id) { return id - 1 - MAX_NPCS; }
