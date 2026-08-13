#pragma once
#include <SDL3/SDL.h>
#include "../../structs/animation/Animation.h"
#include <cstdint>

template<int N>
inline SDL_FRect anchorOrCollision(const Animation<N> &anim, uint32_t index, int frame)
{
    SDL_FRect anchor = {
        anim.frame.anchor.offX[index][frame],
        anim.frame.anchor.offY[index][frame],
        anim.frame.anchor.w[index][frame],
        anim.frame.anchor.h[index][frame]};
    if (anchor.w > 0.0f && anchor.h > 0.0f)
        return anchor;
    return {
        anim.frame.collision.offX[index][frame],
        anim.frame.collision.offY[index][frame],
        anim.frame.collision.w[index][frame],
        anim.frame.collision.h[index][frame]};
}
