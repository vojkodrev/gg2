#pragma once
#include <SDL3/SDL.h>
#include "../../structs/anchors/Anchor.h"

inline SDL_FPoint entityColCenter(const SDL_FRect &r)
{
    return {r.x + r.w * 0.5f, r.y + r.h * 0.5f};
}

template<int NEntities, int NSlots, int NAnchors>
inline SDL_FPoint entityColCenter(
    const Anchor<NEntities, NSlots, NAnchors> &anchor,
    uint32_t index,
    int slot,
    int anchorIndex = 0)
{
    return {
        anchor.offX[index][slot][anchorIndex] +
            anchor.w[index][slot][anchorIndex] * 0.5f,
        anchor.offY[index][slot][anchorIndex] +
            anchor.h[index][slot][anchorIndex] * 0.5f
    };
}
