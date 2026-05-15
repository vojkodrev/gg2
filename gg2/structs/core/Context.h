#pragma once
#include <SDL3/SDL.h>
#include "FrameState.h"
#include "Data.h"
#include "RenderBuffer.h"
#include "KeyboardState.h"
#include "MouseState.h"
#include "../collision/CollisionContext.h"
#include "../gameplay/ai/AStarPool.h"

struct Context
{
    SDL_Renderer *renderer;
    SDL_Texture *texture;

    FrameState frame;
    KeyboardState keyboard;
    MouseState mouse;

    CollisionContext collision;

    AStarPool astarPool;

    Data data;
    RenderBuffer renderBuffer;
};
