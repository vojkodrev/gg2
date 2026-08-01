#pragma once
#include "Context.h"
#include "ClearNpcAiTarget.h"
#include "EntityColAABB.h"
#include "SetNpcAiStateIdle.h"
#include <cstdint>

inline bool setPetIdleIfOffScreen(Context &ctx, uint32_t n)
{
    const SDL_FRect petCol = entityColAABB(ctx.data.npc.base, n);
    const auto &camera = ctx.data.camera;
    const SDL_FRect screenWorld = {
        -camera.offset.x,
        -camera.offset.y,
        camera.screen.w,
        camera.screen.h
    };
    if (SDL_HasRectIntersectionFloat(&petCol, &screenWorld))
        return false;

    ctx.data.npc.autoAttack.active[n] = false;
    clearNpcAiTarget(n, ctx);
    setNpcAiStateIdle(ctx, n);
    return true;
}
