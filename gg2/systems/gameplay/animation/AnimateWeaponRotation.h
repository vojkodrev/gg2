#pragma once
#include "../../../structs/entity/EntityBase.h"
#include <cstdint>

template<int N>
inline void animateWeaponRotation(EntityBase<N> &entityBase, uint32_t i, uint64_t now)
{
    auto &animation = entityBase.animation;
    if (animation.animationType[i] != AnimationType::Rotation)
        return;

    const AnimationState state = animation.animationState[i];
    if (state == AnimationState::Idle || state == AnimationState::Finished)
        return;

    uint64_t duration = animation.cycleDuration[i];
    if (duration == 0)
    {
        animation.animationState[i] = AnimationState::Finished;
        return;
    }

    if (state == AnimationState::Starting)
    {
        animation.animationStartTime[i] = now;
        animation.animationState[i] = AnimationState::Running;
    }

    uint64_t elapsed = now - animation.animationStartTime[i];
    const bool finished = elapsed >= duration;
    if (finished)
        elapsed = duration;

    const float progress = (float)elapsed / (float)duration;
    const float authoredAngle =
        animation.rotationStartAngle[i] +
        (animation.rotationStopAngle[i] - animation.rotationStartAngle[i]) * progress;

    animation.rotate[i] = entityBase.facing.flipX[i]
        ? 360.0f - authoredAngle + entityBase.rotation.initialAngle[i]
        : authoredAngle - entityBase.rotation.initialAngle[i];

    if (finished)
        animation.animationState[i] = AnimationState::Finished;
}
