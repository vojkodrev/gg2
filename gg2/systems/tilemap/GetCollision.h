#pragma once
#include <SDL3/SDL.h>
#include <tmxlite/Tileset.hpp>

SDL_FRect getCollision(const tmx::Tileset &tileset, uint32_t tileIdx);
