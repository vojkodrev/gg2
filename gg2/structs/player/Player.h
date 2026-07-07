#pragma once
#include "../attacks/AutoAttack.h"
#include "../core/EntityBase.h"
#include "../statistics/Statistics.h"
#include "../equipment/Equipment.h"
#include "../ui/Healthbar.h"
#include "../ui/Manabar.h"

struct Player
{
    int groupId = -1;
    int petId = -1;
    int selectedNpc = -1;
    int previousSelectedNpc = -1;
    int selectedEffectId = -1;
    float globalCooldownTimer = 0.0f;
    float concussiveShotCooldownTimer = 0.0f;
    AutoAttack<1> autoAttack;
    EntityBase<1> base;
    Statistics<1> statistics;
    Equipment<1> equipment;
    Healthbar<1> healthbar;
    Manabar<1> manabar;
};
