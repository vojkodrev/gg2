#pragma once
#include <SDL3/SDL.h>
#include "NPC.h"

inline SDL_FRect entityAnchorAABB(const NPC &npc, uint32_t i, float buffer = 0.0f)
{
    int f = npc.base.animation.frameIndex[i];
    return {
        npc.base.position.x[i] + npc.base.animation.frame.anchor.offX[i][f] - buffer,
        npc.base.position.y[i] + npc.base.animation.frame.anchor.offY[i][f] - buffer,
        npc.base.animation.frame.anchor.w[i][f] + buffer * 2,
        npc.base.animation.frame.anchor.h[i][f] + buffer * 2
    };
}
