#pragma once
#include "AStarContext.h"
#include "AStarConstants.h"
#include "../../../utils/pool/Pool.h"

struct AStarPool
{
    AStarContext      ctx[MAX_ASTARS];
    Pool<MAX_ASTARS> pool;
};
