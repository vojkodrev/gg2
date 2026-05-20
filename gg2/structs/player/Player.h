#pragma once
#include "../core/Animation.h"
#include "../equipment/Equipment.h"
#include "../core/EntityPosition.h"
#include "../core/Facing.h"

struct Player
{
    Animation<1> animation;
    EntityPosition<1> position;
    float scale[1];
    Facing<1> facing;
    Equipment<1> equipment;
};
