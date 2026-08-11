#pragma once
#include "../../../structs/entity/EntityBase.h"
#include "../../../utils/collision/EntityColCenter.h"

template<int N>
inline void alignEntityToAnchorCenter(
    EntityBase<N> &entityBase,
    const SDL_FRect &entityAnchor,
    const SDL_FPoint &targetCenterWorld,
    uint32_t i)
{
    const SDL_FPoint entityAnchorCenterLocal = entityColCenter(entityAnchor);

    entityBase.position.x[i] = targetCenterWorld.x - entityAnchorCenterLocal.x;
    entityBase.position.y[i] = targetCenterWorld.y - entityAnchorCenterLocal.y;
}
