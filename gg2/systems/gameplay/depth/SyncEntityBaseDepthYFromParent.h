#pragma once
#include "../../../structs/core/EntityBase.h"
#include <cstdint>

template<int NChild, int NParent>
inline void syncEntityBaseDepthYFromParent(
    EntityBase<NChild> &child,
    const EntityBase<NParent> &parent,
    uint32_t entityIndex)
{
    child.depthY[entityIndex] = parent.depthY[entityIndex];
}
