#pragma once
#include <cstdint>
#include "../core/Group.h"
#include "../core/EntityBase.h"
#include "../core/Statistics.h"
#include "../equipment/Equipment.h"
#include "../ui/Healthbar.h"
#include "NpcConstants.h"
#include "NPCAi.h"

struct NPC
{
    Pool<MAX_NPCS> pool;
    int groupId[MAX_NPCS] = {};
    EntityBase<MAX_NPCS> base;
    Statistics<MAX_NPCS> statistics;
    Equipment<MAX_NPCS> equipment;
    Healthbar<MAX_NPCS> healthbar;
    NPCAi ai;
};
