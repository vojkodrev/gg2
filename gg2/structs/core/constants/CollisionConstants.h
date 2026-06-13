#pragma once
#include <cstdint>

const int MAX_COLLISION_PAIRS = 2048;
constexpr uint32_t COL_TYPE_SHIFT = 24;
constexpr uint32_t COL_INDEX_MASK = (1u << COL_TYPE_SHIFT) - 1u;
