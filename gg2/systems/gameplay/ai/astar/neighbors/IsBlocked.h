#pragma once
#include "../../../../../structs/collision/SpatialHash.h"
#include "../../../../../structs/core/Context.h"

bool isBlocked(const SpatialHash& hash, const Context& ctx, int wx, int wy, SDL_FRect startCol);
