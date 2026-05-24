#pragma once
#include <SDL3/SDL.h>
#include "NPC.h"

inline SDL_FRect entityAnchorAABB(const NPC &npc, uint32_t i, float buffer = 0.0f)
{
    int f = npc.animation.frameIndex[i];
    return {
        npc.position.x[i] + npc.animation.frame.anchor.offX[i][f] - buffer,
        npc.position.y[i] + npc.animation.frame.anchor.offY[i][f] - buffer,
        npc.animation.frame.anchor.w[i][f] + buffer * 2,
        npc.animation.frame.anchor.h[i][f] + buffer * 2
    };
}
