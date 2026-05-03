#pragma once
#include <SDL3/SDL.h>
#include "NPC.h"

inline SDL_FRect entityColAABB(const NPC &npc, uint32_t i, float buffer = 0.0f)
{
    int f = npc.animation.frameIndex[i];
    return {
        npc.position.x[i] + npc.animation.frame.collision.offX[i][f] - buffer,
        npc.position.y[i] + npc.animation.frame.collision.offY[i][f] - buffer,
        npc.animation.frame.collision.w[i][f] + buffer * 2,
        npc.animation.frame.collision.h[i][f] + buffer * 2};
}
