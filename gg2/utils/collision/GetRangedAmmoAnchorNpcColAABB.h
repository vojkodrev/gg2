#pragma once
#include "../../structs/core/Context.h"
#include <SDL3/SDL.h>
#include <cstdint>

inline SDL_FRect getRangedAmmoAnchorNpcColAABB(
    const Context &ctx,
    uint32_t n)
{
    const auto &npc = ctx.data.npc;
    const auto &weapon = npc.equipment.weapon;
    const int frameIndex = weapon.base.animation.frameIndex[n];
    const auto &anchor = npc.rangedCollision.anchor;
    return {
        npc.base.position.x[n] + anchor.offX[n][frameIndex],
        npc.base.position.y[n] + anchor.offY[n][frameIndex],
        anchor.w[n][frameIndex],
        anchor.h[n][frameIndex]
    };
}
