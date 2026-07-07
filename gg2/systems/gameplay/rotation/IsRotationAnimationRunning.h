#pragma once
#include "../../../structs/core/EntityBase.h"
#include <cstdint>

template<int N>
inline bool isRotationAnimationRunning(const EntityBase<N> &entityBase, uint32_t i)
{
    return
        entityBase.animation.animationType[i] == AnimationType::Rotation &&
        entityBase.animation.animationState[i] == AnimationState::Running;
}
