#pragma once
#include <SDL3/SDL.h>
#include "NPC.h"

inline SDL_FRect entityColAABB(const NPC &npc, uint32_t i, float buffer = 0.0f)
{
    return {
        npc.position.x[i] + npc.collision.offX[i] - buffer,
        npc.position.y[i] + npc.collision.offY[i] - buffer,
        npc.collision.w[i] + buffer * 2,
        npc.collision.h[i] + buffer * 2};
}
