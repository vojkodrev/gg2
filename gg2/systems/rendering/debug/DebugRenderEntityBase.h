#pragma once
#include "Context.h"
#include "RenderColBox.h"
#include "../../../utils/collision/EntityColAABB.h"
#include "../../../utils/rect/EntityAnchorAABB.h"

template<int N>
inline void debugRenderEntityBase(
    const Context &ctx,
    const EntityBase<N> &base,
    uint32_t i,
    SDL_Color color,
    SDL_Color anchorColor = SDL_Color{0, 0, 0, 0})
{
    if (anchorColor.a == 0)
        anchorColor = color;

    SDL_FRect colBox = entityColAABB(base, i);
    if (colBox.w > 0.0f && colBox.h > 0.0f)
    {
        SDL_SetRenderDrawColor(ctx.renderer, color.r, color.g, color.b, color.a);
        renderColBox(ctx, colBox);
    }

    SDL_FRect anchorBox = entityAnchorAABB(base, i);
    if (anchorBox.w > 0.0f && anchorBox.h > 0.0f)
    {
        SDL_SetRenderDrawColor(ctx.renderer, anchorColor.r, anchorColor.g, anchorColor.b, anchorColor.a);
        renderColBox(ctx, anchorBox);
    }
}
