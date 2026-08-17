#pragma once
#include "EntityColAABB.h"

template<int NEntities>
inline SDL_FRect mainEntityColAABB(
    const EntityBase<NEntities> &base,
    uint32_t entityIndex,
    float buffer = 0.0f)
{
    return entityColAABB(base, entityIndex, 0, buffer);
}
