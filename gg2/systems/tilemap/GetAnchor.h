#pragma once
#include <SDL3/SDL.h>
#include <cstdint>
#include <tmxlite/Tileset.hpp>

bool getAnchor(
    const tmx::Tileset &tileset,
    uint32_t tileIdx,
    const char *name,
    SDL_FRect &anchor);
