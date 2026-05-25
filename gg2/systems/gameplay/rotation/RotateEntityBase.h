#pragma once
#include "UpdateEntityAnchorAndCollisionRotation.h"
#include "../../../structs/core/EntityBase.h"
#include <cstdint>

template<int N>
inline void rotateEntityBase(EntityBase<N> &entityBase, uint32_t i)
{
    if (entityBase.animation.frameCount[i] == 0)
        return;

    entityBase.rotation.rotate[i] = entityBase.facing.flipX[i]
        ? -entityBase.rotation.initialRotate[i]
        : entityBase.rotation.initialRotate[i];

    updateEntityAnchorAndCollisionRotation(
        entityBase.animation,
        i,
        entityBase.position.w[i],
        entityBase.position.h[i],
        entityBase.rotation.rotate[i]);
}
