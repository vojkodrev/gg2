#pragma once
#include <cstdint>
#include "../attacks/AutoAttack.h"
#include "../core/Group.h"
#include "../core/Groups.h"
#include "../core/EntityBase.h"
#include "../statistics/Statistics.h"
#include "../equipment/Equipment.h"
#include "../ui/Healthbar.h"
#include "../core/constants/IndexConstants.h"
#include "NpcConstants.h"
#include "NPCAi.h"

struct NPC
{
    bool active[MAX_NPCS] = {};
    bool initialized[MAX_NPCS] = {};
    float inactiveTimer[MAX_NPCS] = {};
    Group<MAX_NPCS> group;
    EntityBase<MAX_NPCS> base;
    Statistics<MAX_NPCS> statistics;
    AutoAttack<MAX_NPCS> autoAttack;
    Equipment<MAX_NPCS> equipment;
    Healthbar<MAX_NPCS> healthbar;
    NPCAi ai;
    float concussiveShotDebuffTimer[MAX_NPCS] = {};
    float serpentStingDebuffTimer[MAX_NPCS] = {};

    NPC()
    {
        for (uint32_t i = 0; i < MAX_NPCS; i++)
            group.id[i] = INVALID_ID;
    }
};
