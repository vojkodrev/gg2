#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <tmxlite/Map.hpp>
#include <memory>
#include "Context.h"
#include "LoadTileMap.h"
#include "UpdateFrameStateSystem.h"
#include "FillRenderBufferSystem.h"
#include "RenderSystem.h"
#include "FrameRateLimitSystem.h"
#include "UpdateKeyboardStateSystem.h"
#include "PlayerMovementSystem.h"
#include "CollisionSystem.h"
#include "CollisionResolutionSystem.h"

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("gg2", 1280, 720, 0);
    auto ctx = std::make_unique<Context>();
    ctx->renderer = SDL_CreateRenderer(window, nullptr);

    SDL_Surface *surface = IMG_Load("assets/texture/texture.png");
    ctx->texture = SDL_CreateTextureFromSurface(ctx->renderer, surface);
    SDL_SetTextureScaleMode(ctx->texture, SDL_SCALEMODE_NEAREST);
    SDL_DestroySurface(surface);

    tmx::Map map;
    map.load("assets/map/map1.tmx");

    LoadTileMap(*ctx, map);

    bool running = true;
    SDL_Event event;
    ctx->frame.maxFps = 60;
    ctx->frame.frameCount = 0;
    ctx->frame.lastTicks = SDL_GetTicks();
    while (running)
    {
        UpdateFrameStateSystem(*ctx);

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                running = false;
        }

        UpdateKeyboardStateSystem(*ctx);

        PlayerMovementSystem(*ctx);

        CollisionSystem(*ctx);
        CollisionResolutionSystem(*ctx);

        FillRenderBufferSystem(*ctx);
        RenderSystem(*ctx);

        FrameRateLimitSystem(*ctx);
    }

    SDL_DestroyTexture(ctx->texture);
    SDL_DestroyRenderer(ctx->renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
