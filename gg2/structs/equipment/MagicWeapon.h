#pragma once
#include "../anchors/Anchor.h"
#include "../core/constants/AnimationConstants.h"

template<int N>
struct MagicWeapon
{
    Anchor<N, MAX_ANIMATION_FRAMES, 1> spellAnchor;
    int castingEffectId[N] = {};
};
