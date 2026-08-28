#pragma once
#include <cstdint>
#include <string>
#include <tmxlite/Tileset.hpp>

bool findTileByIcon(
    const tmx::Tileset &tileset,
    const std::string &icon,
    uint32_t &outTileIdx);
