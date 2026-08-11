#pragma once
#include "Animation.h"
#include "EntityPosition.h"
#include "Facing.h"
#include "Rotation.h"
#include "Scale.h"
#include "Tint.h"

template<int N>
struct EntityBase
{
    Animation<N> animation;
    EntityPosition<N> position;
    float depthY[N];
    Scale<N> scale;
    Rotation<N> rotation;
    Facing<N> facing;
    Tint<N> tint;
};
