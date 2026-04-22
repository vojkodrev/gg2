#pragma once
#include "Context.h"
#include <cstdint>

bool isNearColEdge(Context &ctx, uint32_t n, float tx, float ty, float buffer = 0.0f);
