#pragma once
#include "Context.h"
#include "../../../structs/core/EntityType.h"
#include <cstdint>

void executePetAttack(uint32_t n, EntityType targetType, int targetId, Context &ctx);
