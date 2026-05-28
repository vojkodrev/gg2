#pragma once
#include <cstdint>
#include "../core/EntityBase.h"
#include "../equipment/Equipment.h"
#include "CapacityConstants.h"
#include "NPCAi.h"

struct NPC
{
    uint32_t npcCount;
    EntityBase<MAX_NPCS> base;
    Equipment<MAX_NPCS> equipment;
    NPCAi ai;
};
