#pragma once
#include "../../../structs/entity/EntityBase.h"
#include <cstdint>

template<int N>
inline bool isRotationAnimationFinished(const EntityBase<N> &entityBase, uint32_t i)
{
    return
        entityBase.animation.animationType[i] == AnimationType::Rotation &&
        entityBase.animation.animationState[i] == AnimationState::Finished;
}
