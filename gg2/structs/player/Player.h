#pragma once
#include "../attacks/Debuff.h"
#include "../attacks/AutoAttack.h"
#include "../groups/Group.h"
#include "../entity/EntityBase.h"
#include "../core/constants/IndexConstants.h"
#include "../statistics/Statistics.h"
#include "../equipment/Equipment.h"
#include "../ui/CastBar.h"
#include "../ui/ProgressBar.h"

struct Player
{
    Group<1> group;
    int zIndex[1] = {};
    EntityBase<1> base;
    
    int petId = INVALID_ID;
    int previousSelectedNpc = INVALID_ID;
    
    int selectedNpc = INVALID_ID;
    int selectedEffectId = INVALID_ID;
    
    float globalCooldownTimer = 0.0f;
    float concussiveShotCooldownTimer = 0.0f;
    float frostNovaCooldownTimer = 0.0f;
    float targetVisibleTimer = 0.0f;
    
    bool targetVisible = false;
    
    Statistics<1> statistics;
    Equipment<1> equipment;
    
    ProgressBar<1> healthbar;
    ProgressBar<1> manabar;
    CastBar<1> castbar;
    
    AutoAttack<1> autoAttack;
    
    Debuff<1> concussiveShotDebuff;
};
