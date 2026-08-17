#pragma once
#include <SDL3/SDL.h>
#include <cstdint>
#include <tmxlite/Tileset.hpp>

uint32_t getAnchors(
    const tmx::Tileset &tileset,
    uint32_t tileIdx,
    const char *name,
    SDL_FRect *anchors,
    uint32_t maxAnchors);
