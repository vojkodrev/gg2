#pragma once
#include "../../../../../structs/collision/SpatialHash.h"
#include "../../../../../structs/object/Object.h"

bool isBlocked(const SpatialHash& hash, const Object& object, int wx, int wy);
