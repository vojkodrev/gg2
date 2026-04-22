#pragma once
#include <tmxlite/Tileset.hpp>
#include <string>

int getTileProp(const tmx::Tileset &tileset, uint32_t tileIdx, const std::string &name);
std::string getTileStringProp(const tmx::Tileset &tileset, uint32_t tileIdx, const std::string &name);
