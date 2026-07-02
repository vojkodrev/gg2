#pragma once
#include "../../../structs/core/EntityBase.h"
#include <cstdint>

template<int N>
inline void animateWeaponRotation(EntityBase<N> &entityBase, uint32_t i, uint64_t now)
{
    auto &animation = entityBase.animation;
    if (animation.animationType[i] != AnimationType::Rotation)
        return;

    const AnimationState state = animation.animationState[i];
    if (state == AnimationState::Idle)
        return;

    uint64_t duration = animation.cycleDuration[i];
    if (duration == 0)
    {
        animation.rotate[i] =
            entityBase.rotation.initialAngle[i] +
            animation.rotationStopAngle[i];
        animation.animationState[i] = AnimationState::Idle;
        return;
    }

    if (state == AnimationState::Starting)
    {
        animation.animationStartTime[i] = now;
        animation.animationState[i] = AnimationState::Running;
    }

    uint64_t elapsed = now - animation.animationStartTime[i];
    if (elapsed > duration)
        elapsed = duration;

    const float progress = (float)elapsed / (float)duration;
    const float angle =
        entityBase.rotation.initialAngle[i] +
        animation.rotationStartAngle[i] +
        (animation.rotationStopAngle[i] - animation.rotationStartAngle[i]) * progress;

    animation.rotate[i] = angle;

    if (elapsed == duration)
        animation.animationState[i] = AnimationState::Idle;
}
