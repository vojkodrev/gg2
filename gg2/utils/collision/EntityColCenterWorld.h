#pragma once
#include <SDL3/SDL.h>
#include "../../structs/entity/EntityPosition.h"
#include "EntityColCenter.h"

inline SDL_FPoint entityColCenterWorld(const SDL_FRect &r, float x, float y)
{
    const SDL_FPoint localCenter = entityColCenter(r);
    return {x + localCenter.x, y + localCenter.y};
}

template<int N>
inline SDL_FPoint entityColCenterWorld(const SDL_FRect &r, const EntityPosition<N> &position, uint32_t index)
{
    return entityColCenterWorld(r, position.x[index], position.y[index]);
}
