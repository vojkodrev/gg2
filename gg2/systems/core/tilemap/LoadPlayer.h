#pragma once
#include "Context.h"
#include <tmxlite/Map.hpp>
#include <tmxlite/Tileset.hpp>

void LoadPlayer(Context &ctx, const tmx::Map &map, const tmx::Tileset &tileset);
