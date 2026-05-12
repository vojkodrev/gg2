#pragma once
#include "Animation.h"
#include "EntityPosition.h"

template<int N>
struct Equipment
{
    Animation<N> weapon;
    EntityPosition<N> position;
};
