#pragma once
#include "../attacks/AutoAttack.h"
#include "../core/Group.h"
#include "../core/EntityBase.h"
#include "../core/constants/IndexConstants.h"
#include "../statistics/Statistics.h"
#include "../equipment/Equipment.h"
#include "../ui/Healthbar.h"
#include "../ui/Manabar.h"

struct Player
{
    Group<1> group;
    int petId = INVALID_ID;
    int selectedNpc = INVALID_ID;
    int previousSelectedNpc = INVALID_ID;
    int selectedEffectId = INVALID_ID;
    float globalCooldownTimer = 0.0f;
    float concussiveShotCooldownTimer = 0.0f;
    AutoAttack<1> autoAttack;
    EntityBase<1> base;
    Statistics<1> statistics;
    Equipment<1> equipment;
    Healthbar<1> healthbar;
    Manabar<1> manabar;
};
