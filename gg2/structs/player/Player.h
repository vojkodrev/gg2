#pragma once
#include "../core/EntityBase.h"
#include "../core/Statistics.h"
#include "../equipment/Equipment.h"
#include "../ui/Healthbar.h"

struct Player
{
    int groupId = -1;
    EntityBase<1> base;
    Statistics<1> statistics;
    Equipment<1> equipment;
    Healthbar<1> healthbar;
};
