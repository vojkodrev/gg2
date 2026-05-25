#pragma once
#include <SDL3/SDL.h>
#include "NPC.h"

inline SDL_FRect entityColAABB(const NPC &npc, uint32_t i, float buffer = 0.0f)
{
    int f = npc.base.animation.frameIndex[i];
    return {
        npc.base.position.x[i] + npc.base.animation.frame.collision.offX[i][f] - buffer,
        npc.base.position.y[i] + npc.base.animation.frame.collision.offY[i][f] - buffer,
        npc.base.animation.frame.collision.w[i][f] + buffer * 2,
        npc.base.animation.frame.collision.h[i][f] + buffer * 2};
}
