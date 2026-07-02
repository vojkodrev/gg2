#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <tmxlite/Map.hpp>
#include <memory>
#include "Context.h"
#include "ScreenConstants.h"
#include "LoadTileMap.h"
#include "RefreshFrameTiming.h"
#include "FillRenderBufferSystem.h"
#include "RenderSystem.h"
#include "FrameRateLimitSystem.h"
#include "ActionStateSystem.h"
#include "KeyboardStateSystem.h"
#include "debug/DebugFpsSystem.h"
#include "debug/DebugStateSystem.h"
#include "MouseStateSystem.h"
#include "MouseWorldStateSystem.h"
#include "cleanup/DirtyCleanupSystem.h"
#include "PlayerMovementSystem.h"
#include "PlayerFacingSystem.h"
#include "scale/ScalePlayerLocationSystem.h"
#include "scale/ScaleNpcLocationSystem.h"
#include "scale/ScaleObjectLocationSystem.h"
#include "scale/equipment/ScaleEquipmentLocationSystem.h"
#include "flipx/FlipPlayerSystem.h"
#include "depth/PlayerDepthSystem.h"
#include "flipx/FlipNpcSystem.h"
#include "depth/NpcDepthSystem.h"
#include "depth/ObjectDepthSystem.h"
#include "flipx/EquipmentFacingSystem.h"
#include "flipx/FlipEquipmentSystem.h"
#include "depth/EquipmentDepthSystem.h"
#include "depth/BarDepthSystem.h"
#include "depth/EffectDepthSystem.h"
#include "rotation/RotateEquipmentSystem.h"
#include "equipment/MoveEquipmentSystem.h"
#include "attacks/AutoAttackTimerSystem.h"
#include "attacks/ConcussiveShotCooldownTimerSystem.h"
#include "attacks/GlobalCooldownTimerSystem.h"
#include "attacks/PlayerConcussiveShotAttackSystem.h"
#include "attacks/PlayerSerpentStingAttackSystem.h"
#include "attacks/SerpentStingDebuffSystem.h"
#include "attacks/TogglePlayerAutoAttackSystem.h"
#include "attacks/PlayerRangedAutoAttackSystem.h"
#include "effects/MoveEffectSystem.h"
#include "effects/DestroyEffectByTimerSystem.h"
#include "npc/DestroyNpcSystem.h"
#include "npc/NpcAiTimerSystem.h"
#include "npc/select/CreateNpcSelectorSystem.h"
#include "npc/select/DestroyNpcSelectorSystem.h"
#include "npc/select/NpcMouseSelectSystem.h"
#include "npc/select/NpcTabSelectSystem.h"
#include "npc/SpawnNpcSystem.h"
#include "camera/CameraSystem.h"
#include "NPCAiSystem.h"
#include "animation/AnimationSystem.h"
#include "CollisionSystem.h"
#include "EffectCollisionSystem.h"
#include "EffectCollisionResolutionSystem.h"
#include "ui/bars/BarFrameSystem.h"
#include "ui/bars/BarPositionSystem.h"
#include "ui/bars/ShowBarSystem.h"
#include "ui/actionbar/ActionBarTintSystem.h"
#include "tint/DamageTintSystem.h"
#include "tint/CalculateTintSystem.h"
#include "CollisionResolutionSystem.h"

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("gg2", SCREEN_W, SCREEN_H, 0);
    auto ctx = std::make_unique<Context>();
    ctx->renderer = SDL_CreateRenderer(window, NULL);

    SDL_Surface *surface = IMG_Load("assets/texture/texture.png");
    ctx->texture = SDL_CreateTextureFromSurface(ctx->renderer, surface);
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
        refreshFrameTiming(*ctx);

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                running = false;
        }

        keyboardStateSystem(*ctx);
        mouseStateSystem(*ctx);
        actionStateSystem(*ctx);
        debugStateSystem(*ctx);

        debugFpsSystem(*ctx);

        animationSystem(*ctx);

        playerMovementSystem(*ctx);
        playerFacingSystem(*ctx);
        scalePlayerLocationSystem(*ctx);
        flipPlayerSystem(*ctx);
        playerDepthSystem(*ctx);
        
        spawnNpcSystem(*ctx);
        npcAiTimerSystem(*ctx);
        npcAiSystem(*ctx);
        scaleNpcLocationSystem(*ctx);
        flipNpcSystem(*ctx);
        npcDepthSystem(*ctx);
        
        scaleObjectLocationSystem(*ctx);
        objectDepthSystem(*ctx);
        
        collisionSystem(*ctx);
        collisionResolutionSystem(*ctx);
        
        cameraSystem(*ctx);
        mouseWorldStateSystem(*ctx);

        equipmentFacingSystem(*ctx);
        scaleEquipmentLocationSystem(*ctx);
        flipEquipmentSystem(*ctx);
        rotateEquipmentSystem(*ctx);
        moveEquipmentSystem(*ctx);
        equipmentDepthSystem(*ctx);

        autoAttackTimerSystem(*ctx);
        globalCooldownTimerSystem(*ctx);
        concussiveShotCooldownTimerSystem(*ctx);

        togglePlayerAutoAttackSystem(*ctx);

        playerRangedAutoAttackSystem(*ctx);
        playerConcussiveShotAttackSystem(*ctx);
        playerSerpentStingAttackSystem(*ctx);

        serpentStingDebuffSystem(*ctx);

        moveEffectSystem(*ctx);
        destroyEffectByTimerSystem(*ctx);
        effectDepthSystem(*ctx);
        effectCollisionSystem(*ctx);
        effectCollisionResolutionSystem(*ctx);

        destroyNpcSystem(*ctx);

        npcMouseSelectSystem(*ctx);
        npcTabSelectSystem(*ctx);
        destroyNpcSelectorSystem(*ctx);
        createNpcSelectorSystem(*ctx);

        showBarSystem(*ctx);
        barFrameSystem(*ctx);
        barPositionSystem(*ctx);
        barDepthSystem(*ctx);

        actionBarTintSystem(*ctx);
        damageTintSystem(*ctx);
        calculateTintSystem(*ctx);

        dirtyCleanupSystem(*ctx);

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
