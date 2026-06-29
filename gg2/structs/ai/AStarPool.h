#pragma once
#include "AStarContext.h"
#include "../core/constants/AStarConstants.h"
#include "../../utils/pool/Pool.h"

struct AStarPool
{
    AStarContext<MAX_ASTARS> ctx;
    Pool<MAX_ASTARS> pool;
};
