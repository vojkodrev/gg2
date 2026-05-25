#pragma once
#include "../core/EntityBase.h"
#include "../equipment/Equipment.h"

struct Player
{
    EntityBase<1> base;
    Equipment<1> equipment;
};
