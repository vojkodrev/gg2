#pragma once
#include "../../../../../structs/ai/AStarPool.h"

// Returns index into pool.ctx, or -1 if full
int astarAlloc(AStarPool& pool);
