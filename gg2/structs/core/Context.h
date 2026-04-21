#pragma once
#include <SDL3/SDL.h>
#include "FrameState.h"
#include "Data.h"
#include "RenderBuffer.h"
#include "KeyboardState.h"
#include "CollisionResult.h"
#include "SpatialHash.h"

struct Context
{
    SDL_Renderer *renderer;
    SDL_Texture *texture;

    FrameState frame;
    KeyboardState keyboard;

    SpatialHash spatialHash;
    CollisionResult collisions;

    Data data;
    RenderBuffer renderBuffer;
};
