#include "RenderSystem.h"
#include "debug/DebugRenderSystem.h"
#include <SDL3/SDL.h>
#include "../gameplay/camera/GetCameraOffset.h"
#include "Constants.h"

void renderSystem(const Context &ctx)
{
    auto &props = ctx.data.tileMapProps;
    auto &tileMap = ctx.data.tileMap;
    SDL_FPoint off = getCameraOffset(ctx);
    SDL_FRect screen = {0, 0, SCREEN_W, SCREEN_H};
    SDL_RenderClear(ctx.renderer);
    for (uint32_t i = 0; i < tileMap.tileCount; i++)
    {
        SDL_FRect dst = {(float)tileMap.tiles.dstX[i] + off.x, (float)tileMap.tiles.dstY[i] + off.y, (float)props.dstTileW, (float)props.dstTileH};
        if (!SDL_HasRectIntersectionFloat(&dst, &screen))
            continue;
        SDL_FRect src = {(float)tileMap.tiles.srcX[i], (float)tileMap.tiles.srcY[i], (float)props.srcTileW, (float)props.srcTileH};
        SDL_RenderTexture(ctx.renderer, ctx.texture, &src, &dst);
    }
    auto &rb = ctx.renderBuffer;
    for (uint32_t i = 0; i < rb.count; i++)
    {
        SDL_FRect src = {rb.src.x[i], rb.src.y[i], rb.src.w[i], rb.src.h[i]};
        SDL_FRect dst = {rb.dst.x[i], rb.dst.y[i], rb.dst.w[i], rb.dst.h[i]};
        SDL_RenderTexture(ctx.renderer, ctx.texture, &src, &dst);
    }
    debugRenderSystem(ctx);

    SDL_RenderPresent(ctx.renderer);
}
