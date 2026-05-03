#pragma once
#include <cstdint>
#include "../core/SpriteSrc.h"
#include "../core/EntityPosition.h"
#include "../core/EntityCollision.h"
#include "../core/Constants.h"
#include "NPCAi.h"

struct NPC
{
    uint32_t npcCount;
    SpriteSrc<MAX_NPCS> src;
    EntityPosition<MAX_NPCS> position;
    EntityCollision<MAX_NPCS> collision;
    NPCAi ai;
};
