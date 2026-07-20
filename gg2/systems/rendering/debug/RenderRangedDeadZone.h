#pragma once
#include "Context.h"
#include "PlayerConstants.h"

inline void renderRangedDeadZone(const Context &ctx, const SDL_FPoint &center)
{
    const float radius = PLAYER_RANGED_ATTACK_MIN_DISTANCE;
    SDL_FRect rect = {
        center.x - radius + ctx.data.camera.offset.x,
        center.y - radius + ctx.data.camera.offset.y,
        radius * 2.0f,
        radius * 2.0f
    };

    if (SDL_HasRectIntersectionFloat(&rect, &ctx.data.camera.screen))
        SDL_RenderRect(ctx.renderer, &rect);
}
