#pragma once
#include "../core/Animation.h"
#include "../core/Equipment.h"
#include "../core/EntityPosition.h"
#include "../core/Facing.h"

struct Player
{
    Animation<1> animation;
    EntityPosition<1> position;
    Facing<1> facing;
    Equipment<1> equipment;
};
