#pragma once
#include "../../structs/core/Context.h"
#include "../../structs/core/EntityType.h"
#include <cstdint>

float distToEntity(Context &ctx, uint32_t n, EntityType targetType, int targetId);
