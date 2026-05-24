#pragma once
#include <SDL3/SDL.h>
#include "EntityPosition.h"

struct Camera
{
    EntityPosition<1> position;
    SDL_FPoint offset;
    SDL_FRect screen;
};
