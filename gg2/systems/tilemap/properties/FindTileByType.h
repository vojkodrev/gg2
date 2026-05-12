#pragma once
#include <tmxlite/Tileset.hpp>

bool findTileByType(const tmx::Tileset &tileset, const char *type, uint32_t &outTileIdx);
