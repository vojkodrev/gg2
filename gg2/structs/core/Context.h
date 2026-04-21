#pragma once
#include <SDL3/SDL.h>
#include "FrameState.h"
#include "Data.h"
#include "RenderBuffer.h"
#include "KeyboardState.h"
#include "CollisionResult.h"

struct Context
{
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    FrameState frame;
    Data data;
    RenderBuffer renderBuffer;
    KeyboardState keyboard;
    CollisionResult collisions;
};
