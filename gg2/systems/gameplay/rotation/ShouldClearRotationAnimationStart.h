#pragma once
#include "HasMeleeWeaponRotationAnimation.h"
#include "../../../structs/equipment/Weapon.h"
#include "../../../structs/npc/NPCAi.h"
#include <cstdint>

template<int N>
inline bool shouldClearRotationAnimationStart(
    const NPCAi &ai,
    const Weapon<N> &weapon,
    uint32_t i)
{
    return
        ai.state[i] == NPCAiState::ReturnToSpawn &&
        hasMeleeWeaponRotationAnimation(weapon, i);
}
