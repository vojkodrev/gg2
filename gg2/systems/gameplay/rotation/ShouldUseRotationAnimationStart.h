#pragma once
#include "HasMeleeWeaponRotationAnimation.h"
#include "IsRotationAnimationFinished.h"
#include "IsRotationAnimationRunning.h"
#include "../ai/IsNpcAggressive.h"
#include "../../../structs/equipment/Weapon.h"
#include "../../../structs/npc/NPCAi.h"
#include <cstdint>

template<int N>
inline bool shouldUseRotationAnimationStart(
    const NPCAi &ai,
    const Weapon<N> &weapon,
    uint32_t i)
{
    return
        isNpcAggressive(ai, i) &&
        hasMeleeWeaponRotationAnimation(weapon, i) &&
        !isRotationAnimationRunning(weapon.base, i) &&
        !isRotationAnimationFinished(weapon.base, i);
}
