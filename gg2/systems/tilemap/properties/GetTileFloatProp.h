#pragma once
#include <tmxlite/Tileset.hpp>
#include <string>

float getTileFloatProp(const tmx::Tileset &tileset, uint32_t tileIdx, const std::string &name, float defaultVal = 0.0f);
