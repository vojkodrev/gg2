#pragma once
#include <tmxlite/Tileset.hpp>

bool findTileByIcon(const tmx::Tileset &tileset, const char *icon, uint32_t &outTileIdx);
