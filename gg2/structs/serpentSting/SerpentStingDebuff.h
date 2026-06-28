#pragma once
#include <cstdint>
#include "../npc/NpcConstants.h"

struct SerpentStingDebuff
{
    float debuffTime[MAX_NPCS] = {};
    float debuffTimer[MAX_NPCS] = {};
    bool debuffActive[MAX_NPCS] = {};
};
