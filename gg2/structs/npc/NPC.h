#pragma once
#include <cstdint>
#include "../core/Animation.h"
#include "../core/EntityPosition.h"
#include "../core/Facing.h"
#include "../equipment/Equipment.h"
#include "CapacityConstants.h"
#include "NPCAi.h"

struct NPC
{
    uint32_t npcCount;
    Animation<MAX_NPCS> animation;
    EntityPosition<MAX_NPCS> position;
    Facing<MAX_NPCS> facing;
    Equipment<MAX_NPCS> equipment;
    NPCAi ai;
};
