#pragma once
#include "../core/EntityBase.h"
#include "../equipment/Equipment.h"

struct Player
{
    int groupId = -1;
    EntityBase<1> base;
    Equipment<1> equipment;
};
