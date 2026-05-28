#pragma once
#include "Animation.h"
#include "EntityPosition.h"
#include "Facing.h"
#include "Rotation.h"

template<int N>
struct EntityBase
{
    Animation<N> animation;
    EntityPosition<N> position;
    float scale[N];
    Rotation<N> rotation;
    Facing<N> facing;
};
