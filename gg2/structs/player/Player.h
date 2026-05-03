#pragma once
#include "../core/SpriteSrc.h"
#include "../core/EntityPosition.h"
#include "../core/EntityCollision.h"

struct Player
{
    SpriteSrc<1> src;
    EntityPosition<1> position;
    EntityCollision<1> collision;
};
