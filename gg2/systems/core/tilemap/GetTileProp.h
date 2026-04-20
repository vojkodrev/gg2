#pragma once
#include <tmxlite/Tileset.hpp>
#include <string>

int GetTileProp(const tmx::Tileset &tileset, uint32_t tileIdx, const std::string &name);
