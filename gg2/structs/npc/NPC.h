#pragma once
#include <cstdint>
#include "../attacks/AggroTable.h"
#include "../attacks/AutoAttack.h"
#include "../attacks/Debuff.h"
#include "../groups/Group.h"
#include "../groups/Groups.h"
#include "../entity/EntityBase.h"
#include "../anchors/CenteredAnchor.h"
#include "../core/constants/AnimationConstants.h"
#include "../statistics/Statistics.h"
#include "../equipment/Equipment.h"
#include "../ui/ProgressBar.h"
#include "../core/constants/IndexConstants.h"
#include "NpcConstants.h"
#include "NPCAi.h"

struct NPC
{
    bool active[MAX_NPCS] = {};
    bool initialized[MAX_NPCS] = {};
    float inactiveTimer[MAX_NPCS] = {};
    float globalCooldownTimer[MAX_NPCS] = {};
    float concussiveShotCooldownTimer[MAX_NPCS] = {};
    float tauntTimer[MAX_NPCS] = {};
    Group<MAX_NPCS> group;
    int zIndex[MAX_NPCS] = {};
    EntityBase<MAX_NPCS> base;
    Statistics<MAX_NPCS> statistics;
    AutoAttack<MAX_NPCS> autoAttack;
    AggroTable<MAX_NPCS> aggroTable;
    Equipment<MAX_NPCS> equipment;
    CenteredAnchor<MAX_NPCS, MAX_ANIMATION_FRAMES> rangedCollision;
    ProgressBar<MAX_NPCS> healthbar;
    ProgressBar<MAX_NPCS> manabar;
    NPCAi ai;
    Debuff<MAX_NPCS> concussiveShotDebuff;
    Debuff<MAX_NPCS> frostNovaDebuff;
    Debuff<MAX_NPCS> serpentStingDebuff;
    Debuff<MAX_NPCS> arcaneExplosionDebuff;

    NPC()
    {
        for (uint32_t i = 0; i < MAX_NPCS; i++)
            group.id[i] = INVALID_ID;
    }
};
