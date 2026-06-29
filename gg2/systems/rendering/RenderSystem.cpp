#include "RenderSystem.h"
#include "debug/DebugRenderSystem.h"
#include <SDL3/SDL.h>
#include <cmath>

void renderSystem(const Context &ctx)
{
    auto &props = ctx.data.tileMapProps;
    auto &tileMap = ctx.data.tileMap;
    const SDL_FPoint off = ctx.data.camera.offset;
    const SDL_FRect screen = ctx.data.camera.screen;
    SDL_SetTextureScaleMode(ctx.texture, SDL_SCALEMODE_PIXELART);
    SDL_SetRenderDrawColor(ctx.renderer, 0, 0, 0, 255);
    SDL_RenderClear(ctx.renderer);
    for (uint32_t i = 0; i < tileMap.tileCount; i++)
    {
        SDL_FRect dst = {
            std::round((float)tileMap.tiles.dstX[i] + off.x),
            std::round((float)tileMap.tiles.dstY[i] + off.y),
            (float)props.dstTileW,
            (float)props.dstTileH
        };
        if (!SDL_HasRectIntersectionFloat(&dst, &screen))
            continue;
        SDL_FRect src = {(float)tileMap.tiles.srcX[i], (float)tileMap.tiles.srcY[i], (float)props.srcTileW, (float)props.srcTileH};
        SDL_RenderTexture(ctx.renderer, ctx.texture, &src, &dst);
    }
    auto &rb = ctx.renderBuffer;
    for (uint32_t i = 0; i < rb.count; i++)
    {
        SDL_FRect src = {rb.src.x[i], rb.src.y[i], rb.src.w[i], rb.src.h[i]};
        SDL_FRect dst = {
            std::round(rb.dst.x[i]),
            std::round(rb.dst.y[i]),
            rb.dst.w[i],
            rb.dst.h[i]
        };
        SDL_FPoint rotationCenter = {rb.rotationCenter.point.x[i], rb.rotationCenter.point.y[i]};
        SDL_FPoint *center = rb.rotationCenter.hasCenter[i] ? &rotationCenter : nullptr;
        SDL_FlipMode flip = rb.flipX[i] ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
        SDL_SetTextureColorModFloat(ctx.texture, rb.tint.r[i], rb.tint.g[i], rb.tint.b[i]);
        SDL_SetTextureAlphaModFloat(ctx.texture, rb.tint.a[i]);
        SDL_RenderTextureRotated(ctx.renderer, ctx.texture, &src, &dst, rb.src.rotate[i], center, flip);
    }
    SDL_SetTextureColorModFloat(ctx.texture, 1.0f, 1.0f, 1.0f);
    SDL_SetTextureAlphaModFloat(ctx.texture, 1.0f);
    debugRenderSystem(ctx);

    SDL_RenderPresent(ctx.renderer);
}
