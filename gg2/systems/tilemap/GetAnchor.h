#pragma once
#include <SDL3/SDL.h>
#include <tmxlite/Tileset.hpp>

SDL_FRect getAnchor(const tmx::Tileset &tileset, uint32_t tileIdx, const char *name);
