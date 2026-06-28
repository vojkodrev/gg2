#pragma once
#include <cstdint>
#include "../core/constants/NpcConstants.h"

struct SerpentStingDebuff
{
    float debuffTime[MAX_NPCS] = {};
    float debuffTimer[MAX_NPCS] = {};
    bool debuffActive[MAX_NPCS] = {};
};
