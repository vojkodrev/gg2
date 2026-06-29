#pragma once
#include <SDL3/SDL.h>
#include "FrameState.h"
#include "Data.h"
#include "RenderBuffer.h"
#include "../ai/AStarPool.h"
#include "../input/KeyboardState.h"
#include "../input/MouseState.h"
#include "../collision/CollisionContext.h"

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
