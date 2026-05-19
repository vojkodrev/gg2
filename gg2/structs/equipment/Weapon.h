#pragma once
#include "../core/Animation.h"
#include "../core/EntityPosition.h"

template<int N>
struct Weapon
{
    Animation<N> animation;
    EntityPosition<N> position;
};
