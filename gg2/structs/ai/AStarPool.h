#pragma once
#include "AStarContext.h"
#include "../core/constants/AStarConstants.h"
#include "../../utils/pool/Pool.h"

struct AStarPool
{
    AStarContext<MAX_ASTARS> ctx;
    Pool<1, MAX_ASTARS> pool;
};
