#pragma once
#include <SDL3/SDL.h>
#include "FrameState.h"
#include "Data.h"
#include "RenderBuffer.h"
#include "KeyboardState.h"
#include "../collision/CollisionContext.h"
#include "../gameplay/ai/AStarContext.h"
#include "Constants.h"

struct Context
{
    SDL_Renderer *renderer;
    SDL_Texture *texture;

    FrameState frame;
    KeyboardState keyboard;

    CollisionContext collision;

    Data data;
    RenderBuffer renderBuffer;

    AStarContext astar[MAX_ASTARS];
};
