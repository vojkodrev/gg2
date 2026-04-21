#pragma once
#include <cstdint>
#include "NPCSrc.h"
#include "NPCPosition.h"
#include "NPCCollision.h"
#include "NPCAi.h"

struct NPC
{
    uint32_t npcCount;
    NPCSrc src;
    NPCPosition position;
    NPCCollision collision;
    NPCAi ai;
};
