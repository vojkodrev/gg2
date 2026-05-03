#pragma once
#include "../core/Animation.h"
#include "../core/EntityPosition.h"

struct Player
{
    Animation<1> animation;
    EntityPosition<1> position;
};
