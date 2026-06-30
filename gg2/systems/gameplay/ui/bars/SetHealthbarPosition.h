#pragma once
#include "../../../structs/core/EntityBase.h"
#include "../../../structs/core/constants/HealthbarConstants.h"
#include <cstdint>

template<int N>
inline void setHealthbarPosition(
    EntityBase<N> &healthbarBase,
    const EntityBase<N> &parentBase,
    uint32_t index)
{
    healthbarBase.position.x[index] =
        parentBase.position.x[index] +
        (parentBase.position.w[index] - healthbarBase.position.w[index]) * 0.5f;
    healthbarBase.position.y[index] =
        parentBase.position.y[index] -
        healthbarBase.position.h[index] -
        HEALTHBAR_DISTANCE_FROM_ENTITY;
}
