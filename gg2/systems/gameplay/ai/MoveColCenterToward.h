#pragma once
#include "Context.h"
#include <cstdint>

void moveColCenterToward(Context &ctx, uint32_t n, SDL_FPoint target, float speed);
