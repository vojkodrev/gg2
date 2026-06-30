#pragma once
#include "Health.h"
#include "Mana.h"

template<int N>
struct Statistics
{
    Health<N> health;
    Mana<N> mana;
};
