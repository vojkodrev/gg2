#pragma once
#include <tmxlite/Tileset.hpp>
#include <string>

std::string getTileStringProp(const tmx::Tileset &tileset, uint32_t tileIdx, const std::string &name);
