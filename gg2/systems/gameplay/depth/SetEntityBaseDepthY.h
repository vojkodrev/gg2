#pragma once
#include "../../../structs/entity/EntityBase.h"
#include <cstdint>

template<int N>
inline void setEntityBaseDepthY(EntityBase<N> &entityBase, uint32_t entityIndex)
{
    int frameIndex = entityBase.animation.frameIndex[entityIndex];
    entityBase.depthY[entityIndex] =
        entityBase.position.y[entityIndex] +
        entityBase.animation.frame.collision.offY[entityIndex][frameIndex][0];
}
