#pragma once
#include "../../structs/core/EntityPosition.h"
#include <SDL3/SDL.h>

template<int N>
inline SDL_FPoint entityPositionCenter(const EntityPosition<N> &position, uint32_t i)
{
    return {
        position.x[i] + position.w[i] * 0.5f,
        position.y[i] + position.h[i] * 0.5f
    };
}
