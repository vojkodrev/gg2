#pragma once
#include "../core/Animation.h"
#include "../core/EntityPosition.h"
#include "../core/Facing.h"
#include "../core/Rotation.h"

template<int N>
struct Ammo
{
    Animation<N> animation;
    EntityPosition<N> position;
    float scale[N];
    Rotation<N> rotation;
    Facing<N> facing;
};
