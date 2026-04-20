#pragma once
#include <tmxlite/Tileset.hpp>

void GetCollision(const tmx::Tileset &tileset, uint32_t tileIdx, float &offX, float &offY, float &w, float &h);
