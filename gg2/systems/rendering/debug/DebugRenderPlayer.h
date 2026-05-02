#pragma once
#include "Context.h"
#include <SDL3/SDL.h>

void debugRenderPlayer(SDL_Renderer *renderer, const Context &ctx, SDL_FPoint off, const SDL_FRect &screen);
