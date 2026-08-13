#pragma once
#include <SDL3/SDL.h>
#include "../../structs/anchors/Anchor.h"

inline SDL_FPoint entityColCenter(const SDL_FRect &r)
{
    return {r.x + r.w * 0.5f, r.y + r.h * 0.5f};
}

template<int NItems, int NSlots>
inline SDL_FPoint entityColCenter(const Anchor<NItems, NSlots> &anchor, uint32_t index, int slot)
{
    return {
        anchor.offX[index][slot] + anchor.w[index][slot] * 0.5f,
        anchor.offY[index][slot] + anchor.h[index][slot] * 0.5f
    };
}
