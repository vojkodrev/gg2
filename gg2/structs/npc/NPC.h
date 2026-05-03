#pragma once
#include <cstdint>
#include "../core/Animation.h"
#include "../core/EntityPosition.h"
#include "../core/Constants.h"
#include "NPCAi.h"

struct NPC
{
    uint32_t npcCount;
    Animation<MAX_NPCS> animation;
    EntityPosition<MAX_NPCS> position;
    NPCAi ai;
};
