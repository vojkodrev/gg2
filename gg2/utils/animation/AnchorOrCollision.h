#pragma once
#include <SDL3/SDL.h>
#include "../../structs/animation/Animation.h"
#include <cstdint>

template<int N>
inline SDL_FRect anchorOrCollision(const Animation<N> &anim, uint32_t index, int frame)
{
    SDL_FRect anchor = {
        anim.frame.anchor.offX[index][frame][0],
        anim.frame.anchor.offY[index][frame][0],
        anim.frame.anchor.w[index][frame][0],
        anim.frame.anchor.h[index][frame][0]};
    if (anchor.w > 0.0f && anchor.h > 0.0f)
        return anchor;
    return {
        anim.frame.collision.offX[index][frame][0],
        anim.frame.collision.offY[index][frame][0],
        anim.frame.collision.w[index][frame][0],
        anim.frame.collision.h[index][frame][0]};
}
