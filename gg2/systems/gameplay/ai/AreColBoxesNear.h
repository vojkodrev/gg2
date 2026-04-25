#pragma once
#include "Context.h"
#include <SDL3/SDL.h>
#include <cstdint>

bool areColBoxesNear(Context &ctx, uint32_t n, const SDL_FRect &targetCol, float buffer);
