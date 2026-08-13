#pragma once
#include <cstdlib>

inline int calculateAttackDamage(int baseDamage, int randomRange)
{
    if (randomRange <= 0)
        return baseDamage;

    const int damageRandom =
        (rand() % (randomRange + 1)) -
        randomRange / 2;
    return baseDamage - damageRandom;
}
