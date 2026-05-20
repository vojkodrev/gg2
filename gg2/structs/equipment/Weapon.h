#pragma once
#include "../core/Animation.h"
#include "../core/EntityPosition.h"
#include "../core/Facing.h"

template<int N>
struct Weapon
{
    Animation<N> animation;
    EntityPosition<N> position;
    float scale[N];
    Facing<N> facing;
};
