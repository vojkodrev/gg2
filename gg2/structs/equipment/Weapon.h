#pragma once
#include "../core/Animation.h"
#include "../core/Facing.h"

template<int N>
struct Weapon
{
    Animation<N> animation;
    float scale[N];
    Facing<N> facing;
};
