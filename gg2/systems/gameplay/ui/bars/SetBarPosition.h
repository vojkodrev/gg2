#pragma once
#include "../../../structs/entity/EntityBase.h"
#include "../../../structs/core/constants/HealthbarConstants.h"
#include <cstdint>

template<int N>
inline void setBarPosition(
    EntityBase<N> &barBase,
    const EntityBase<N> &parentBase,
    float yOffset,
    uint32_t index)
{
    barBase.position.x[index] =
        parentBase.position.x[index] +
        (parentBase.position.w[index] - barBase.position.w[index]) * 0.5f;
    barBase.position.y[index] =
        parentBase.position.y[index] -
        barBase.position.h[index] -
        HEALTHBAR_DISTANCE_FROM_ENTITY +
        yOffset;
}
