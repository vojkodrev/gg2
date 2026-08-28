#pragma once
#include <cstdint>
#include <string>
#include <tmxlite/Tileset.hpp>

bool findTileByType(
    const tmx::Tileset &tileset,
    const std::string &type,
    uint32_t &outTileIdx);
