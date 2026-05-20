#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <tmxlite/Map.hpp>
#include <memory>
#include "Context.h"
#include "ScreenConstants.h"
#include "LoadTileMap.h"
#include "UpdateFrameStateSystem.h"
#include "FillRenderBufferSystem.h"
#include "RenderSystem.h"
#include "FrameRateLimitSystem.h"
#include "UpdateKeyboardStateSystem.h"
#include "UpdateMouseStateSystem.h"
#include "PlayerMovementSystem.h"
#include "PlayerFacingSystem.h"
#include "EquipmentSystem.h"
#include "camera/CameraSystem.h"
#include "NPCAiSystem.h"
#include "animation/AnimationSystem.h"
#include "CollisionSystem.h"
#include "CollisionResolutionSystem.h"

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("gg2", SCREEN_W, SCREEN_H, 0);
    auto ctx = std::make_unique<Context>();
    ctx->renderer = SDL_CreateRenderer(window, NULL);

    SDL_Surface *surface = IMG_Load("assets/texture/texture.png");
    ctx->texture = SDL_CreateTextureFromSurface(ctx->renderer, surface);
    SDL_SetTextureScaleMode(ctx->texture, SDL_SCALEMODE_NEAREST);
    SDL_DestroySurface(surface);

    tmx::Map map;
    map.load("assets/map/map1.tmx");

    ctx->data.camera.position.w[0] = SCREEN_W;
    ctx->data.camera.position.h[0] = SCREEN_H;

    loadTileMap(*ctx, map);

#ifndef NDEBUG
    SDL_Log("Renderer: %s", SDL_GetRendererName(ctx->renderer));
#endif

    bool running = true;
    SDL_Event event;
    ctx->frame.maxFps = 120;
    ctx->frame.frameCount = 0;
    ctx->frame.lastTicks = SDL_GetTicks();
    while (running)
    {
        updateFrameStateSystem(*ctx);

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                running = false;
        }

        updateKeyboardStateSystem(*ctx);
        updateMouseStateSystem(*ctx);

        playerMovementSystem(*ctx);
        cameraSystem(*ctx);
        playerFacingSystem(*ctx);
        equipmentSystem(*ctx);
        npcAiSystem(*ctx);
        animationSystem(*ctx);

        collisionSystem(*ctx);
        collisionResolutionSystem(*ctx);

        fillRenderBufferSystem(*ctx);
        renderSystem(*ctx);

        frameRateLimitSystem(*ctx);
    }

    SDL_DestroyTexture(ctx->texture);
    SDL_DestroyRenderer(ctx->renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
