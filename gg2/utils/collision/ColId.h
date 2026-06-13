#pragma once
#include "CollisionConstants.h"
#include "EffectConstants.h"
#include "NpcConstants.h"
#include "ObjectConstants.h"
#include <cstdint>

inline uint16_t colIdNpc(uint32_t i)    { return (uint16_t)(1 + i); }
inline uint16_t colIdObject(uint32_t i) { return (uint16_t)(1 + MAX_NPCS + i); }
inline uint16_t colIdEffect(uint32_t i) { return (uint16_t)(1 + MAX_NPCS + MAX_OBJECTS + i); }

inline bool colIdIsPlayer(uint16_t id) { return id == COLLISION_ENTITY_PLAYER; }
inline bool colIdIsNpc(uint16_t id)    { return id >= 1 && id <= (uint16_t)MAX_NPCS; }
inline bool colIdIsObject(uint16_t id)
{
    return id > (uint16_t)MAX_NPCS && id <= (uint16_t)(MAX_NPCS + MAX_OBJECTS);
}
inline bool colIdIsEffect(uint16_t id) { return id > (uint16_t)(MAX_NPCS + MAX_OBJECTS); }

inline uint32_t colIdNpcIndex(uint16_t id)    { return id - 1; }
inline uint32_t colIdObjectIndex(uint16_t id) { return id - 1 - MAX_NPCS; }
inline uint32_t colIdEffectIndex(uint16_t id) { return id - 1 - MAX_NPCS - MAX_OBJECTS; }
